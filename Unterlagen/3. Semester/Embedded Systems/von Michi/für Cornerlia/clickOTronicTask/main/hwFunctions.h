/*
 * hwFunctions.h
 *
 *  Created on: 24.10.2022
 *      Author: admin
 */

#ifndef MAIN_HWFUNCTIONS_H_
#define MAIN_HWFUNCTIONS_H_

#define LIGHT_INTENSITY						15

typedef enum{
	green,
	blue,
	red,
	amber,
	pink,
	dark
}color_t;


void configure_led(void);
void setLedColor(color_t color);



#endif /* MAIN_HWFUNCTIONS_H_ */
