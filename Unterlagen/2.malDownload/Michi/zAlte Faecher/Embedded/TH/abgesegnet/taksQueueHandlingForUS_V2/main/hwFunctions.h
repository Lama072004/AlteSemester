/*
 * hwFunctions.h
 *
 *  Created on: 24.10.2022
 *      Author: admin
 */

#ifndef MAIN_HWFUNCTIONS_H_
#define MAIN_HWFUNCTIONS_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/sigmadelta.h"



//GPIO's
#define TRIG							GPIO_NUM_0
#define ECHO							GPIO_NUM_1
#define TRIG2							GPIO_NUM_7
#define ECHO2							GPIO_NUM_6
#define TONE_PIN 						GPIO_NUM_2
#define ON_OFF							GPIO_NUM_9
#define SDM_OUTPUT						GPIO_NUM_5
#define VOLUME_CONTROL_OUT					GPIO_NUM_5

extern TaskHandle_t timeToDistance_tHandle;
extern TaskHandle_t sendMeasurementCommand1_tHandle;
extern TaskHandle_t sendMeasurementCommand2_tHandle;
extern QueueHandle_t queSignalHandler;

void configurePeriphery();
void buzzerPlayTone(uint8_t pin, uint64_t frq, uint16_t duration);
void noTone(int pin);
void buzzerPlayTone(uint8_t pin, uint64_t frq, uint16_t duration);
void sigmadelta_init_OWN(void);
void configure_buzzer(int toneGpioNum);
void configure_volumeControl();
void buzzerChangeVolume(uint32_t duty);

#endif /* MAIN_HWFUNCTIONS_H_ */
