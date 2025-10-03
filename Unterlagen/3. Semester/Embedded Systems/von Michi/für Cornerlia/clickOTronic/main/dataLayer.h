/*
 * dataLayer.h
 *
 *  Created on: 09.10.2022
 *      Author: Michael
 */

#ifndef MAIN_DATALAYER_H_
#define MAIN_DATALAYER_H_


#define MIN_TIME_TO_CLICK					2000000 //us
#define MAX_TIME_TILL_LOSS					5000000
#define TIME_WINDOW							3000000
#define MAX_REACTION_TIME					500500


typedef enum{
	notStarted,
	started,
	next,
	lost
}gameState_t;

void configureDataLayer();
void gameLogic();


#endif /* MAIN_DATALAYER_H_ */
