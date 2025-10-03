/*
 * misc.h
 *
 *  Created on: 29.12.2022
 *      Author: admin
 */

#ifndef MAIN_MISC_H_
#define MAIN_MISC_H_

#include <stdint.h>

//distances in mm
#define MAX_DISTANCE					( 506 )
#define MIN_DISTANCE					( 50 )
#define DELTA_DISTANCE					( MAX_DISTANCE - MIN_DISTANCE )
#define COUNT_OF_OCTAVES				( 1 )
// calculate step size. Ideally  this is a whole number -> 456mm / 8 = 57mm
#define STEP_SIZE_MM					( DELTA_DISTANCE / (COUNT_OF_OCTAVES * 8) )

#define STARTING_TONE					( TONE_IDX_A4 )

typedef struct signalEvent_s
{
	enum{
		changeVolume,
		changeTone
	}signalType;
	uint64_t val;
}signalEvent_t;

void waitForMicros(uint64_t delay);
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);



#endif /* MAIN_MISC_H_ */
