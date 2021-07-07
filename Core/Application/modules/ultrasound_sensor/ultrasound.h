/*
 * proximity.h
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_MODULES_ULTRASOUND_SENSOR_ULTRASOUND_H_
#define APPLICATION_MODULES_ULTRASOUND_SENSOR_ULTRASOUND_H_

#include "stdbool.h"
#include "stdint.h"
#include "main.h"
#include "stm32l1xx.h"
#include "FreeRTOS.h"
#include "timers.h"

typedef enum {

	evgroup_ultrasound_evbit_echo = 0,
	evgroup_valve_evbit_N,

} evgroup_ultrasound_bits_t;

bool ultrasound_init(void);

/*
 * need to waits 10us
 */
void ultrasound_trig(void);

void timer_ultrasound_sensor_tigger(TimerHandle_t xTimer);

#endif /* APPLICATION_MODULES_ULTRASOUND_SENSOR_ULTRASOUND_H_ */
