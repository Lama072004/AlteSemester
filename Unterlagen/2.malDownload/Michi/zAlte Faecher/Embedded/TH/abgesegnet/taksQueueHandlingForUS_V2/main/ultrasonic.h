/*
 * ultrasonic.h
 *
 *  Created on: 03.12.2022
 *      Author: GEM
 *      timing:
 *		trigger to high
 *		hold 10us
 *		trigger to low
 *		interrupt anyedge && echo == high -> save time
 *		interrupt anyedge && echo == low -> get time difference
 *		if difference > 200ms -> no signal detected
 *		minimum tim between measurements 20ms (datasheet) --> why??
 *
 *
 */

#ifndef MAIN_ULTRASONIC_H_
#define MAIN_ULTRASONIC_H_

#define MILLIS_TO_MICROS				(1000)
#define MICROS_TO_NANOS					(1000)
#define MILLIS_TO_NANOS					(1000000)

#define TIMECONSTANT_AT_20DEG			(5830)			//nanoseconds per millimeter, WHOLE RUNTIME forth AND back

//all times in micros
#define TIM_TRIGGER_HOLD_LOW			(10)
#define TIM_NO_DETECTION				(200   * MILLIS_TO_MICROS)


uint64_t getDistance(uint64_t elapsedTime);


#endif /* MAIN_ULTRASONIC_H_ */
