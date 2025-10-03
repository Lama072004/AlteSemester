/*
 * hwFunctions.c
 *
 *  Created on: 24.10.2022
 *      Author: admin
 */

#include "hwFunctions.h"
#include "led_strip.h"

static led_strip_t *pStrip_a;

#define BLINK_GPIO 							CONFIG_BLINK_GPIO



void setLedColor(color_t color)
{
	switch (color)
	{
	case green:
        pStrip_a->set_pixel(pStrip_a, 0, 0, LIGHT_INTENSITY, 0);
        break;
	case blue:
        pStrip_a->set_pixel(pStrip_a, 0, 0, 0, LIGHT_INTENSITY);
        break;
	case red:
        pStrip_a->set_pixel(pStrip_a, 0, LIGHT_INTENSITY, 0, 0);
        break;
	case amber:
        pStrip_a->set_pixel(pStrip_a, 0, LIGHT_INTENSITY, (int)((float)LIGHT_INTENSITY * 0.75f) , 0);
        break;
	case pink:
        pStrip_a->set_pixel(pStrip_a, 0, LIGHT_INTENSITY, (int)((float)LIGHT_INTENSITY * 0.65f) , (int)((float)LIGHT_INTENSITY * 0.6f));
        break;
	case dark:
        pStrip_a->clear(pStrip_a, 50);
        break;
	default:
		break;
	}
	pStrip_a->refresh(pStrip_a, 100);
}

void configure_led(void)
{

    pStrip_a = led_strip_init(CONFIG_BLINK_LED_RMT_CHANNEL, BLINK_GPIO, 1);

    pStrip_a->clear(pStrip_a, 50);
}



