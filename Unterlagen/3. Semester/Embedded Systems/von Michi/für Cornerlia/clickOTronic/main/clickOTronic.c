/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

#include "hwFunctions.h"


void gameLogic();
void configureDataLayer();

#define BUTTON_INPUT				9
#define BLINK_GPIO 					CONFIG_BLINK_GPIO
#define LIGHT_INTENSITY				15

static const char *TAG = "CLKOTRON";
static led_strip_t *pStrip_a;

static fpSetNewTimestamp fpCBSetNewTimestamp = NULL;

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink addressable LED!");
    /* LED strip initialization with the GPIO and pixels number*/
    pStrip_a = led_strip_init(CONFIG_BLINK_LED_RMT_CHANNEL, BLINK_GPIO, 1);
    /* Set all LED off to clear all pixels */
    pStrip_a->clear(pStrip_a, 50);
}

void registerCallbackButtonEvent(fpSetNewTimestamp fp)
{
	fpCBSetNewTimestamp = fp;
}


void setLedColor(color_t color)
{
	switch (color)
	{
	case red:
        pStrip_a->set_pixel(pStrip_a, 0, LIGHT_INTENSITY, 0, 0);
        break;
	case green:
        pStrip_a->set_pixel(pStrip_a, 0, 0, LIGHT_INTENSITY, 0);
        break;
	case blue:
        pStrip_a->set_pixel(pStrip_a, 0, 0, 0, LIGHT_INTENSITY);
        break;
	case dark:
        pStrip_a->clear(pStrip_a, 50);
        break;
	default:
		break;
	}
	pStrip_a->refresh(pStrip_a, 100);
}

void IRAM_ATTR isrButtonWasPressed(void* v)
{
	if(fpCBSetNewTimestamp)
	{
		fpCBSetNewTimestamp(esp_timer_get_time());
	}
}

void configureHW()
{
	gpio_config_t input = {
			.pin_bit_mask = (1 << BUTTON_INPUT),
			.mode = GPIO_MODE_INPUT,
			.intr_type = GPIO_INTR_NEGEDGE,
			.pull_up_en = GPIO_PULLUP_ENABLE,
			.pull_down_en = GPIO_PULLDOWN_DISABLE
	};
	gpio_config(&input);
	gpio_install_isr_service(0);
	gpio_isr_handler_add(BUTTON_INPUT, isrButtonWasPressed, 0);

	configure_led();
	ESP_LOGI(TAG, "HW conifg done");
}

void app_main(void)
{
	configureHW();
	configureDataLayer();
	while(true)
	{
		gameLogic();
	}
}
