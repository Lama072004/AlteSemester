/*
 * ledc.h
 *
 *  Created on: 29.12.2022
 *      Author: admin
 */

#ifndef MAIN_LEDC_CFG_H_
#define MAIN_LEDC_CFG_H_

#include "driver/ledc.h"

//Tone configuration
#define TONE_LEDC_TIMER              	LEDC_TIMER_0
#define TONE_LEDC_MODE               	LEDC_LOW_SPEED_MODE
#define TONE_LEDC_CHANNEL            	LEDC_CHANNEL_0
#define TONE_LEDC_DUTY_RES           	LEDC_TIMER_13_BIT // Set duty resolution to 13 bits GEM: is equal to numerical 13
#define TONE_LEDC_MAX_DUTY				( (1 << TONE_LEDC_DUTY_RES ) - 1 )
#define TONE_LEDC_DUTY_50_PERCENT		( TONE_LEDC_MAX_DUTY / 2 )
#define TONE_LEDC_DUTY_OFF				( 0 )
#define TONE_LEDC_START_FREQ			( 200 )

#define TONE_LEDC_MIN_FREQ				( NOTE_A2 )
#define TONE_LEDC_MAX_FREQ				( NOTE_A5 )


//Volume configuration
#define VOLUME_LEDC_TIMER              	LEDC_TIMER_1
#define VOLUME_LEDC_MODE               	LEDC_LOW_SPEED_MODE
#define VOLUME_LEDC_CHANNEL            	LEDC_CHANNEL_1
#define VOLUME_LEDC_DUTY_RES           	LEDC_TIMER_10_BIT // Set duty resolution to 13 bits GEM: is equal to numerical 13
#define VOLUME_LEDC_MAX_DUTY			( (1 << VOLUME_LEDC_DUTY_RES ) - 1 )
#define VOLUME_LEDC_DUTY_50_PERCENT		( VOLUME_LEDC_MAX_DUTY / 2 )
#define VOLUME_LEDC_DUTY_OFF			( 0 )
#define VOLUME_LEDC_START_FREQ			( 70000 )

#endif /* MAIN_LEDC_CFG_H_ */
