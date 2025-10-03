/*
 * ultrasonic.c
 *
 *  Created on: 29.12.2022
 *      Author: admin
 */

#include <stdint.h>
#include "ultrasonic.h"

//returns distance in millimeters
uint64_t getDistance(uint64_t elapsedTime)
{
	//elapsed time * 1000 -> time in ns
	//divided by time constant
	return (elapsedTime * 1000) / TIMECONSTANT_AT_20DEG;
}

