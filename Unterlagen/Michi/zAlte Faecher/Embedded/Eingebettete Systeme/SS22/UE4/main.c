#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

/*
 * CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
 * Watch CPU0 Idle Task has been disabled! Software PWM is "starving" the CPU because of the tick counter
 * Found in: Component config > ESP System Settings > CONFIG_ESP_TASK_WDT
 * With watchdog enabled there's a flick every 5seconds
 */

#define SENSE_SWITCH_SPEED GPIO_NUM_9
#define LED_ACTIVE_HIGH GPIO_NUM_6
#define LED_ACTIVE_LOW GPIO_NUM_7

enum dwellState_e{
	brighter,
	darker,
};

esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}

void app_main(void)
{
	gpio_reset_pin(LED_ACTIVE_HIGH);
	gpio_reset_pin(LED_ACTIVE_LOW);									//no response if pins are not resetted

	gpio_set_direction(LED_ACTIVE_HIGH, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_ACTIVE_LOW, GPIO_MODE_OUTPUT);

    gpio_set_direction(SENSE_SWITCH_SPEED, GPIO_MODE_INPUT);

    enum dwellState_e dwellState = brighter;
    uint8_t flagSpeedSwitch = 0;
    uint32_t pwmStep = 20;
    uint32_t dutyCycle = 0;
    uint32_t maximumTickCount = 6000; 								//approximated frequency of 200Hz,

    volatile uint32_t tickCount = 0;

    while (true) {
    	tickCount += 1;
    	if(tickCount > maximumTickCount){
    		tickCount = 0;
    		if(dwellState == brighter){
    			dutyCycle += pwmStep;
    		}else if(dwellState == darker){
    			dutyCycle -= pwmStep;
    		}
    	}

    	if(dwellState == brighter && dutyCycle > maximumTickCount){
    		dwellState = darker;
    	}else if(dwellState == darker && dutyCycle <= pwmStep){
    		dwellState = brighter;
    	}
    	if(tickCount < dutyCycle){
    		gpio_set_level(LED_ACTIVE_HIGH, 1);
    		gpio_set_level(LED_ACTIVE_LOW, 1);
    	}else{
    		gpio_set_level(LED_ACTIVE_HIGH, 0);
    		gpio_set_level(LED_ACTIVE_LOW, 0);
    	}

    	if(!gpio_get_level(SENSE_SWITCH_SPEED) && !flagSpeedSwitch){
    		if(pwmStep < 50){
    			pwmStep += 10;
    		}else{
    			pwmStep = 20;
    		}
    		ESP_LOGI("Heartbeat.c", "New PWM step value %d", pwmStep);
    		flagSpeedSwitch = true;
    	}
    	if(gpio_get_level(SENSE_SWITCH_SPEED)){
    		flagSpeedSwitch = false;
    	}

    }
}

