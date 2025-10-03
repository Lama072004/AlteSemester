/*
 * hwFunctions.c
 *
 *  Created on: 24.10.2022
 *      Author: admin
 */

#include <ledc_cfg.h>
#include "hwFunctions.h"
#include "ultrasonic.h"
#include "misc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#include "driver/ledc.h"



void IRAM_ATTR isrEchoDetection1(void* pV);
void IRAM_ATTR isrEchoDetection2(void* pV);
void waitForMicros(uint64_t delay);


void noTone(int pin)
{
	ledc_timer_pause(TONE_LEDC_MODE, TONE_LEDC_TIMER);
	sigmadelta_set_duty(SIGMADELTA_CHANNEL_0, -127);
}

void buzzerPlayTone(uint8_t pin, uint64_t frq, uint16_t duration)
{
	ledc_timer_resume(TONE_LEDC_MODE, TONE_LEDC_TIMER);
	ledc_set_freq(TONE_LEDC_MODE, TONE_LEDC_TIMER, frq);
}

void buzzerChangeVolume(uint32_t duty)
{
	uint32_t maxDuty = (1 << VOLUME_LEDC_DUTY_RES) - 1;
	duty = duty > maxDuty ? maxDuty : duty;
	ledc_set_duty_and_update(VOLUME_LEDC_MODE, VOLUME_LEDC_CHANNEL, duty, 0);
}

void configure_volumeControl()
{
	//first PWM signal is used to create the frequency, respectively tone
	{
		// Prepare and then apply the LEDC PWM timer configuration
		ledc_timer_config_t ledc_timer = {
				.speed_mode       = VOLUME_LEDC_MODE,
				.timer_num        = VOLUME_LEDC_TIMER,
				.duty_resolution  = VOLUME_LEDC_DUTY_RES,
				.freq_hz          = VOLUME_LEDC_START_FREQ,  // Set output frequency to 20 kHz
				.clk_cfg          = LEDC_AUTO_CLK
		};
		ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

		ledc_channel_config_t ledc_channel = {
				.speed_mode     = VOLUME_LEDC_MODE,
				.channel        = VOLUME_LEDC_CHANNEL,
				.timer_sel      = VOLUME_LEDC_TIMER,
				.intr_type      = LEDC_INTR_DISABLE,
				.gpio_num       = VOLUME_CONTROL_OUT,
				.duty           = 0,
				.hpoint         = 0
		};
		ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
	}
	ledc_fade_func_install(0);
#ifdef DEBUG_LVL1
	ESP_LOGI("VOL", "cfg finished");
#endif
}


void sigmadelta_init_OWN(void)
{
	sigmadelta_config_t sigmadelta_cfg = {
			.channel = SIGMADELTA_CHANNEL_0,
			.sigmadelta_prescale = 80,
			.sigmadelta_duty = 0,
			.sigmadelta_gpio = SDM_OUTPUT,
	};
	sigmadelta_config(&sigmadelta_cfg);
}

void configure_buzzer(int toneGpioNum)
{
	//first PWM signal is used to create the frequency, respectively tone
	{
		// Prepare and then apply the LEDC PWM timer configuration
		ledc_timer_config_t ledc_timer = {
				.speed_mode       = TONE_LEDC_MODE,
				.timer_num        = TONE_LEDC_TIMER,
				.duty_resolution  = TONE_LEDC_DUTY_RES,
				.freq_hz          = TONE_LEDC_START_FREQ,  // Set output frequency at 5 kHz
				.clk_cfg          = LEDC_AUTO_CLK
		};
		ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

		uint16_t dutyCycle50Percent = ( (1 << TONE_LEDC_DUTY_RES) - 1 ) / 2;
		// Prepare and then apply the LEDC PWM channel configuration
		ledc_channel_config_t ledc_channel = {
				.speed_mode     = TONE_LEDC_MODE,
				.channel        = TONE_LEDC_CHANNEL,
				.timer_sel      = TONE_LEDC_TIMER,
				.intr_type      = LEDC_INTR_DISABLE,
				.gpio_num       = (int)toneGpioNum,
				.duty           = dutyCycle50Percent,   // Set duty to 0% Range [0, 2**duty_resolution]
				//50% for all the time should be ok
				.hpoint         = 0
		};
		ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
	}
}


void configurePeriphery()
{
	/* Configure the peripheral according to the LED type */
	{
		gpio_config_t cfgEcho = {
				.intr_type = GPIO_INTR_ANYEDGE,
				.mode = GPIO_MODE_INPUT,
				.pin_bit_mask = (1 << ECHO),
				.pull_down_en = GPIO_PULLDOWN_DISABLE,
				.pull_up_en =  GPIO_PULLUP_ENABLE
		};
		gpio_config_t cfgTrig = {
				.pin_bit_mask = (1 << TRIG),
				.mode = GPIO_MODE_OUTPUT,
				.pull_down_en = GPIO_PULLDOWN_DISABLE,
				.pull_up_en = GPIO_PULLUP_DISABLE,
				.intr_type = GPIO_INTR_DISABLE
		};

		gpio_config_t cfgEcho2 = {
				.intr_type = GPIO_INTR_ANYEDGE,
				.mode = GPIO_MODE_INPUT,
				.pin_bit_mask = (1 << ECHO2),
				.pull_down_en = GPIO_PULLDOWN_DISABLE,
				.pull_up_en =  GPIO_PULLUP_ENABLE
		};
		gpio_config_t cfgTrig2 = {
				.pin_bit_mask = (1 << TRIG2),
				.mode = GPIO_MODE_OUTPUT,
				.pull_down_en = GPIO_PULLDOWN_DISABLE,
				.pull_up_en = GPIO_PULLUP_DISABLE,
				.intr_type = GPIO_INTR_DISABLE
		};
		gpio_config(&cfgTrig);
		gpio_config(&cfgEcho);
		gpio_config(&cfgTrig2);
		gpio_config(&cfgEcho2);


		gpio_install_isr_service(0);
		gpio_isr_handler_add(ECHO, isrEchoDetection1, NULL);
		gpio_isr_handler_add(ECHO2, isrEchoDetection2, NULL);
	}
	//set defined state
	gpio_set_level(TRIG, true);
	gpio_set_level(TRIG2, true);
	//wait for sensor to settle down
	waitForMicros(TIM_NO_DETECTION);
}

static int64_t sUS1wasSentAt ;
void IRAM_ATTR isrEchoDetection1(void* pV)
{
	(void) pV;

	if(gpio_get_level(ECHO))
	{
		//burst signal was sent
		sUS1wasSentAt = esp_timer_get_time();
	}
	else
	{
		//echo arrived
		signalEvent_t se =
		{
				.signalType = changeVolume,
				.val = esp_timer_get_time() - sUS1wasSentAt
		};
		xQueueSendFromISR(queSignalHandler, (void*) &se, queueSEND_TO_BACK );
		xTaskResumeFromISR(sendMeasurementCommand1_tHandle);
	}
}

static int64_t sUS2wasSentAt ;
void IRAM_ATTR isrEchoDetection2(void* pV)
{
	(void) pV;

	if(gpio_get_level(ECHO2))
	{
		//burst signal was sent
		sUS2wasSentAt = esp_timer_get_time();
	}
	else
	{
		//echo arrived
		signalEvent_t se =
		{
				.signalType = changeTone,
				.val = esp_timer_get_time() - sUS2wasSentAt
		};
		xQueueSendFromISR(queSignalHandler, (void*) &se, queueSEND_TO_BACK );
		xTaskResumeFromISR(sendMeasurementCommand2_tHandle);
	}
}


