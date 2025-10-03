/*
 * dataLayer.c
 *
 *  Created on: 06.10.2022
 *      Author: admin
 */

#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_random.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "hwFunctions.h"

#include "dataLayer.h"

static const char* TAG = "CLKTRONIC_DL";
static gameState_t actualState = notStarted;

static int64_t lastClickedAt = 0;
static int64_t timeLedBlueOn = 0;
static int64_t timeTillLoss = 0;
static int64_t maxReactionTime = MAX_REACTION_TIME;

//returns a random float between 0 and 1
float getRandom()
{
	return ((float) esp_random() / 0xFFFFFFFF);
}

void setNewTimestamp(int64_t timestamp)
{
	lastClickedAt  = timestamp;
}

void configureDataLayer()
{
	registerCallbackButtonEvent(setNewTimestamp);
	ESP_LOGI(TAG, "DL conifg done");
}

void gameLogic()
{
	static int64_t tempClicked = 0;
	switch(actualState)
	{
	case notStarted:
		if(lastClickedAt > tempClicked && tempClicked != lastClickedAt)
		{
			actualState = next;
		}
		break;
	case started:
		if(esp_timer_get_time() - timeTillLoss > 0 ||
				(esp_timer_get_time() - timeLedBlueOn < 0 && tempClicked != lastClickedAt))
		{
			setLedColor(red);
			actualState = lost;
		}
		else if(esp_timer_get_time() - (timeLedBlueOn + lastClickedAt) < maxReactionTime && tempClicked != lastClickedAt)
		{
			setLedColor(green);
			actualState = next;
		}
		else if(esp_timer_get_time() - timeLedBlueOn > 0)
		{
			setLedColor(blue);
		}
		break;
	case next:
		vTaskDelay(100);
		timeLedBlueOn = esp_timer_get_time() + MIN_TIME_TO_CLICK + (int64_t)((double)TIME_WINDOW * getRandom());
		timeTillLoss = timeLedBlueOn + maxReactionTime;
		maxReactionTime -= 500;
		setLedColor(dark);
		actualState = started;
		break;
	case lost:
		setLedColor(red);
		ESP_LOGI(TAG, "You Lost!");
		vTaskDelay(1000);
		actualState = notStarted;
		break;
	default:
		break;

	}
	tempClicked = lastClickedAt;
}


