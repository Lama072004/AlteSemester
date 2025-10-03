/*
 * misc.c
 *
 *  Created on: 29.12.2022
 *      Author: admin
 */

#include <stdint.h>
#include "esp_timer.h"

//copied from arduino lib
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void waitForMicros(uint64_t delay)
{
	uint64_t timeNow = esp_timer_get_time();
	while(esp_timer_get_time() - timeNow < delay);
}
