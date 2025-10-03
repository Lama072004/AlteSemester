/*
 * hwFunctions.h
 *
 *  Created on: 06.10.2022
 *      Author: admin
 */

#ifndef MAIN_HWFUNCTIONS_H_
#define MAIN_HWFUNCTIONS_H_

typedef enum{
	green,
	blue,
	red,
	dark
}color_t;


typedef void (*fpSetNewTimestamp) (int64_t timestamp);
void setLedColor(color_t color);

void registerCallbackButtonEvent(fpSetNewTimestamp fp);

#endif /* MAIN_HWFUNCTIONS_H_ */
