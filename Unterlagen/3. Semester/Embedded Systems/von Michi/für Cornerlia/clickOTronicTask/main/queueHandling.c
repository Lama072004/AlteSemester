/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

#include "hwFunctions.h"


typedef enum {
	pressed,
	released
}keyState_t ;

typedef struct{
	keyState_t keyState;
	int64_t timestamp;
}KeyEvent_t;

typedef enum
{
	notStarted,
	started,
	newEvent,
	lost
}gameState_t;

typedef struct{
	gameState_t gameState;
	int64_t lastKeyPress;
}game_t;

QueueHandle_t queKeyhandler;


#define BUTTON_INPUT						9

#define LED_TASK_STACK_SIZE					2048
#define TASK_INPUT_PRIORITY					3
#define TASK_TOGGLE_PRIORITY				3

static const char *TAG = "example";

TaskHandle_t taskReadInput = NULL;
TaskHandle_t toggleLed = NULL;


void readInputFunc(void* pV)
{
	(void) pV;
	bool lastState = false;
	while(true){
		bool actState = gpio_get_level(BUTTON_INPUT);
		if(actState != lastState)
		{
			KeyEvent_t ke = {
					.keyState = actState,
					.timestamp = esp_timer_get_time()
			};
			xQueueSend(queKeyhandler, (void*) &ke, ( TickType_t ) 10);
		}
		lastState = actState;
		vTaskDelay( 10 / portTICK_PERIOD_MS);
	}
}

void gameMainLogic(void* pV)
{
	(void) pV;
	color_t actColor = dark;
	KeyEvent_t newEvent = { 0 };
	game_t game = { 0 };

	while(true){
		if(xQueueReceive(queKeyhandler, &newEvent,(TickType_t) 10))
		{
			switch(game.gameState)
			{
			case notStarted:
				game.gameState = started;
				break;
			case started:
				game.gameState = newEvent;
				break;
			default:
				break;
			}

			actColor +=1;

			if(actColor == dark)
			{
				actColor = 0;
			}

		}

		if(game.gameState != notStarted)
		{

		}




		vTaskDelay( 10 / portTICK_PERIOD_MS);
	}
}


void app_main(void)
{
	/* Configure the peripheral according to the LED type */
	{
		configure_led();
		gpio_config_t cfg = {
				.intr_type = GPIO_INTR_DISABLE,
				.mode = GPIO_MODE_INPUT,
				.pin_bit_mask = (1 << BUTTON_INPUT),
				.pull_down_en = GPIO_PULLDOWN_DISABLE,
				.pull_up_en =  GPIO_PULLUP_ENABLE
		};
		gpio_config(&cfg);
	}

    queKeyhandler = xQueueCreate(10, sizeof (KeyEvent_t));

    xTaskCreate(readInputFunc, "READIN", LED_TASK_STACK_SIZE, NULL, TASK_INPUT_PRIORITY, &taskReadInput);
    xTaskCreate(gameMainLogic, "MAINLOGIC", LED_TASK_STACK_SIZE, NULL, TASK_TOGGLE_PRIORITY, &toggleLed);
    //configASSERT(ledRedTask);
   // configASSERT(ledBlueTask);

    while (1) {
    	vTaskDelay( 100 / portTICK_PERIOD_MS);

    }
}
