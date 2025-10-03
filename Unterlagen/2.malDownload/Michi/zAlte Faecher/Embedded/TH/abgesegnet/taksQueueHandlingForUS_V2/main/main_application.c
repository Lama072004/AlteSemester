/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
 */
#include <ledc_cfg.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "driver/gpio.h"
#include "driver/sigmadelta.h"
#include "driver/ledc.h"

#include "esp_system.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_adc_cal.h"

#include "led_strip.h"
#include "sdkconfig.h"

#include "hwFunctions.h"
#include "ultrasonic.h"
#include "pitches.h"
#include "misc.h"


#define TIME_BETWEEN_MEASUREMENTS			( 10000 )


//#define DEBUG_			//lvl 1, watch out, interface gets flooded with msg's
#define DEBUG__				//lvl 2

#define ISR_FLAG	0
#define TONE_HYSTERESIS_MM						25

extern const uint32_t pitches[];
extern const uint32_t majorScale[];

//Task cfg
#define TASK_DETECT_STACK_SIZE					2048
#define TASK_INPUT_PRIORITY						3
#define TASK_DETECT_PRIORITY					3

//TaskHandle_t detectionUS2_tHandle = NULL;
TaskHandle_t timeToDistance_tHandle = NULL;
TaskHandle_t sendMeasurementCommand1_tHandle= NULL;
TaskHandle_t sendMeasurementCommand2_tHandle = NULL;
TaskHandle_t setSpeakerValues_tHandle = NULL;

QueueHandle_t queSignalHandler = NULL;
QueueHandle_t queDistanceHandler = NULL;

void setSpeakerValues();
void sendMeasurementCommand1();
void sendMeasurementCommand2();
void timeToDistance(void* pV);


#define MAX_DISTANCE_VOLUME			400
#define MIN_DISTANCE_VOLUME			50


int cnt1 = 0;

void normAndSetVolume(int64_t val)
{
	int64_t inBounds = val;
	if(val > MAX_DISTANCE_VOLUME) inBounds = MAX_DISTANCE_VOLUME;
	if(val < 0) inBounds = 0;
	inBounds /=10;
	inBounds *=10;
	int8_t normedVal = map((int32_t)inBounds, 0,
			MAX_DISTANCE_VOLUME, 0, 110);
//#ifdef DEBUG
	if(cnt1%100 == 0)
	ESP_LOGI("NormAndSetVol", "raw Val: %lld, normed: %d, inBounds", val, normedVal, inBounds);
//#endif

	sigmadelta_set_duty(SIGMADELTA_CHANNEL_0, 110);
	cnt1++;
}

void setSpeakerValues()
{
	uint8_t indexOfToneToPlay = 0;
	uint8_t offsetOfToneToPlay = 0;
	bool speakerIsOn = false;
	bool lastStateSwitch = gpio_get_level(ON_OFF);
	while(1)
	{
		if(lastStateSwitch != gpio_get_level(ON_OFF) && gpio_get_level(ON_OFF))
		{
			speakerIsOn = !speakerIsOn;
			ESP_LOGI("SPK", "Is %s", speakerIsOn ? "on" : "off");
		}
		lastStateSwitch = gpio_get_level(ON_OFF);

		if(speakerIsOn)
		{
			signalEvent_t ev = { 0 };
			if(xQueueReceive(queDistanceHandler,  &ev, 100))
			{
				if(ev.signalType == changeVolume)
				{
					normAndSetVolume(ev.val);
				}
				else if(ev.signalType == changeTone)
				{
					uint32_t distance = ev.val - MIN_DISTANCE;
					uint32_t upperBound = (offsetOfToneToPlay + 1) * STEP_SIZE_MM + TONE_HYSTERESIS_MM;
					uint32_t lowerBound = offsetOfToneToPlay > 0 ? (offsetOfToneToPlay * STEP_SIZE_MM - TONE_HYSTERESIS_MM) : 0;
					if (distance > MAX_DISTANCE){
						//distance is too far to be counted
						continue;
					}
					int i= -1;
#ifdef DEBUG__
					ESP_LOGI("DBG", "dist: %d\tUB: %d, LB: %d", distance, upperBound, lowerBound);
#endif
					if(distance > upperBound || distance <= lowerBound)
					{//hyteresis for new tone
						for(i = 0; i < COUNT_OF_OCTAVES * 8; i += 1)
						{//find new tone
							if(distance < (i + 1) * STEP_SIZE_MM)
							{//new tone found
								break;
							}
						}
					}
					if(i >= 0 && i != 8)
					{
						noTone(TONE_PIN);
						//play a different tone
						indexOfToneToPlay = majorScale[i % 8] + STARTING_TONE;
						offsetOfToneToPlay = i;
						buzzerPlayTone(TONE_PIN, pitches[indexOfToneToPlay], 0);
#ifdef DEBUG__
						ESP_LOGI("TONE", "idx: %d\t\tofs: %d", indexOfToneToPlay, offsetOfToneToPlay);
#endif
					}//endif
				}//endif signaltype
			}//no queue availaible
		}//speaker not on

		else
		{
			noTone(TONE_PIN);
			xQueueReset(queDistanceHandler);
		}
		vTaskDelay( 10 / portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
	configurePeriphery();
	sigmadelta_init_OWN();
	sigmadelta_set_duty(SIGMADELTA_CHANNEL_0, -20);

	//configure_volumeControl();
	configure_buzzer(TONE_PIN);

	queSignalHandler = xQueueCreate(10, sizeof (signalEvent_t));
	queDistanceHandler = xQueueCreate(10, sizeof (signalEvent_t));

	xTaskCreate(timeToDistance, "Conversion", TASK_DETECT_STACK_SIZE, NULL, TASK_DETECT_PRIORITY, &timeToDistance_tHandle);
	xTaskCreate(setSpeakerValues, "Speaker", TASK_DETECT_STACK_SIZE, NULL, TASK_DETECT_PRIORITY, &setSpeakerValues_tHandle);

	xTaskCreate(sendMeasurementCommand1, "sendMeas1", TASK_DETECT_STACK_SIZE, NULL, TASK_DETECT_PRIORITY, &sendMeasurementCommand1_tHandle);
	xTaskCreate(sendMeasurementCommand2, "sendMeas2", TASK_DETECT_STACK_SIZE, NULL, TASK_DETECT_PRIORITY, &sendMeasurementCommand2_tHandle);

	while (1) {
		vTaskDelay( 10 / portTICK_PERIOD_MS);
	}
}

void sendMeasurementCommand1()
{
	int64_t timeLastSent = esp_timer_get_time();
	while(1)
	{
		//wait for at minimum 20ms for next measurement
		if(esp_timer_get_time() - timeLastSent > TIME_BETWEEN_MEASUREMENTS)
		{
			gpio_set_level(TRIG, false);
			waitForMicros(TIM_TRIGGER_HOLD_LOW);
			//ESP_LOGI("MEAS", "active");
			//TODO: Implement the correct time delay. Acts weird with vTaskDelay
			//vTaskDelay(10 / portTICK_PERIOD_MS);
			gpio_set_level(TRIG, true);
			timeLastSent = esp_timer_get_time();
			vTaskSuspend(sendMeasurementCommand1_tHandle);  //suspend till echo arrived
		}
		vTaskDelay(1);
	}
}

void sendMeasurementCommand2()
{
	int64_t timeLastSent = esp_timer_get_time();
	while(1)
	{
		//wait for at minimum 20ms for next measurement
		if(esp_timer_get_time() - timeLastSent > TIME_BETWEEN_MEASUREMENTS)
		{
			gpio_set_level(TRIG2, false);
			waitForMicros(TIM_TRIGGER_HOLD_LOW);
			//ESP_LOGI("MEAS", "active");
			//TODO: Implement the correct time delay. Acts weird with vTaskDelay
			//vTaskDelay(10 / portTICK_PERIOD_MS);
			gpio_set_level(TRIG2, true);
			timeLastSent = esp_timer_get_time();
			vTaskSuspend(sendMeasurementCommand2_tHandle); //suspend till echo arrived
		}
		vTaskDelay(1);
	}
}



void timeToDistance(void* pV)
{
	(void) pV;
	signalEvent_t rcvEvent = { 0 };
	signalEvent_t txEvent = { 0 };
	while(true)
	{
		while(uxQueueMessagesWaiting(queSignalHandler))
		{
			if(xQueueReceive(queSignalHandler, &rcvEvent, (TickType_t) 100))
			{
				txEvent.signalType = rcvEvent.signalType;
				txEvent.val = getDistance(rcvEvent.val);
				xQueueSend(queDistanceHandler, (void*) &txEvent, 10);
#ifdef DEBUG_
				ESP_LOGI("RCV", "%sValue was: %lld, distance: %lld", rcvEvent.signalType == changeTone ? "changing Tone, " : "changing Vol,  "
						, rcvEvent.val, getDistance(rcvEvent.val));
#endif
			}
		}
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}


