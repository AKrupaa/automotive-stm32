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

// velocity of sound in air 0.0344 cm/us
// htim10 -> 100000 Hz -> max mean 10us, resolution = 10us / ((counter period) 319) = 31.25 nanoseconds = 0,03125 us

// odleglosc [cm] = czas [us] * 0.0344 cm/us
// czyli
// odleglosc [cm] = (htim10 * 0,03125 us) * 0.0344 cm/us
// czas [us] = odleglosc cm / ( 0.0344 cm/us )
#define TIMER_10_RESOLUTION			0.03125 	// microseconds
// 5 cm / ( 0.0344 cm/us )
#define ULTRASOUND_DIST_5CM 		145.348837 	// microseconds
#define ULTRASOUND_DIST_10CM 		290.697674 	// microseconds
#define ULTRASOUND_DIST_15CM 		436.046512 	// microseconds
#define ULTRASOUND_DIST_20CM 		581.395349 	// microseconds
#define ULTRASOUND_DIST_25CM 		726.744186 	// microseconds
#define ULTRASOUND_DIST_30CM 		872.093023 	// microseconds
//#define ULTRASOUND_DIST_35CM 		1.01744186 	// milliseconds
#define ULTRASOUND_DIST_35CM 		1017.44186 	// microseconds
#define ULTRASOUND_DIST_40CM 		1162.7907  	// microseconds

#define ULTRASOUND_DIST_5CM_BITS 	((ULTRASOUND_DIST_5CM) / TIMER_10_RESOLUTION)   // ULTRASOUND_DIST_5CM / RESOLUTION
//															145.348837 us / 0.03125 us =
//															= 4651.162784 BITS == 4652 BITS from timer
#define ULTRASOUND_DIST_10CM_BITS 	((ULTRASOUND_DIST_10CM) / TIMER_10_RESOLUTION)
#define ULTRASOUND_DIST_15CM_BITS 	((ULTRASOUND_DIST_15CM) / TIMER_10_RESOLUTION)
#define ULTRASOUND_DIST_20CM_BITS 	((ULTRASOUND_DIST_20CM) / TIMER_10_RESOLUTION)
#define ULTRASOUND_DIST_25CM_BITS 	((ULTRASOUND_DIST_25CM) / TIMER_10_RESOLUTION)
#define ULTRASOUND_DIST_30CM_BITS 	((ULTRASOUND_DIST_30CM) / TIMER_10_RESOLUTION)
#define ULTRASOUND_DIST_35CM_BITS 	((ULTRASOUND_DIST_35CM) / TIMER_10_RESOLUTION)
#define ULTRASOUND_DIST_40CM_BITS 	((ULTRASOUND_DIST_40CM) / TIMER_10_RESOLUTION)

typedef enum {
	evgroup_ultrasound_evbit_echo = 0,
	evgroup_ultrasound_evbit_move,
	evgroup_valve_evbit_N,

} evgroup_ultrasound_bits_t;

bool ultrasound_init(void);

/*
 * need to waits 10us
 */
void ultrasound_trig(void);

void timer_ultrasound_sensor_tigger(TimerHandle_t xTimer);

#endif /* APPLICATION_MODULES_ULTRASOUND_SENSOR_ULTRASOUND_H_ */
