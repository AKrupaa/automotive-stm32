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
// htim10 -> 100000 Hz -> max mean 10us, resolution = CLK / PSC (prescaler) = 0.125 us

// odleglosc [cm] = czas [us] * 0.0344 cm/us
// czyli
// odleglosc [cm] = (htim10 * 0,03125 us) * 0.0344 cm/us
// czas [us] = odleglosc cm / ( 0.0344 cm/us )
#define TIMER_10_RESOLUTION			((float)0.125)//0.03125 	// microseconds
// 5 cm / ( 0.0344 cm/us )
#define ULTRASOUND_DIST_5CM 		((float)145.348837) 	// microseconds
#define ULTRASOUND_DIST_10CM 		((float)290.697674) 	// microseconds
#define ULTRASOUND_DIST_15CM 		((float)436.046512) 	// microseconds
#define ULTRASOUND_DIST_20CM 		((float)581.395349) 	// microseconds
#define ULTRASOUND_DIST_25CM 		((float)726.744186) 	// microseconds
#define ULTRASOUND_DIST_30CM 		((float)872.093023) 	// microseconds
//#define ULTRASOUND_DIST_35CM 		1.01744186 	// milliseconds
#define ULTRASOUND_DIST_35CM 		((float)1017.44186) 	// microseconds
#define ULTRASOUND_DIST_40CM 		((float)1162.7907)  	// microseconds
#define ULTRASOUND_DIST_50CM 		((float)1162.7907 + ULTRASOUND_DIST_10CM)  	// microseconds
#define ULTRASOUND_DIST_60CM 		((float)1162.7907 + 2* ULTRASOUND_DIST_10CM )  	// microseconds
#define ULTRASOUND_DIST_70CM 		((float)1162.7907 + 3 * ULTRASOUND_DIST_10CM)  	// microseconds
#define ULTRASOUND_DIST_80CM 		((float) 8 * ULTRASOUND_DIST_10CM)  	// microseconds

#define ULTRASOUND_DIST_5CM_BITS 	((ULTRASOUND_DIST_5CM) / TIMER_10_RESOLUTION)   // ULTRASOUND_DIST_5CM / RESOLUTION
//															145.348837 us / 0.03125 us =
//															= 4651.162784 BITS == 4652 BITS from timer
#define ULTRASOUND_DIST_10CM_BITS 	(((ULTRASOUND_DIST_10CM) / TIMER_10_RESOLUTION * 2))
#define ULTRASOUND_DIST_15CM_BITS 	((ULTRASOUND_DIST_15CM) / TIMER_10_RESOLUTION * 2)
#define ULTRASOUND_DIST_20CM_BITS 	((ULTRASOUND_DIST_20CM) / TIMER_10_RESOLUTION * 2)
#define ULTRASOUND_DIST_25CM_BITS 	((ULTRASOUND_DIST_25CM) / TIMER_10_RESOLUTION * 2)
#define ULTRASOUND_DIST_30CM_BITS 	((ULTRASOUND_DIST_30CM) / TIMER_10_RESOLUTION * 2)
#define ULTRASOUND_DIST_35CM_BITS 	((ULTRASOUND_DIST_35CM) / TIMER_10_RESOLUTION * 2)
#define ULTRASOUND_DIST_40CM_BITS 	((ULTRASOUND_DIST_40CM) / TIMER_10_RESOLUTION * 2)
#define ULTRASOUND_DIST_50CM_BITS 	((ULTRASOUND_DIST_50CM) / TIMER_10_RESOLUTION * 2)
#define ULTRASOUND_DIST_60CM_BITS 	((ULTRASOUND_DIST_60CM) / TIMER_10_RESOLUTION * 2)
#define ULTRASOUND_DIST_70CM_BITS 	((ULTRASOUND_DIST_70CM) / TIMER_10_RESOLUTION * 2)
#define ULTRASOUND_DIST_80CM_BITS 	((ULTRASOUND_DIST_80CM) / TIMER_10_RESOLUTION * 2)

extern volatile uint16_t ULTRASOUND_PROPER_DISTANCE_u16;

typedef enum {
	evgroup_ultrasound_evbit_echo = 0,
	evgroup_ultrasound_evbit_move,
	evgroup_valve_evbit_N,

} evgroup_ultrasound_bits_t;

typedef enum {
	dist5 = 0,
	dist10,
	dist15,
	dist20,
	dist25,
	dist30,
	dist35,
	dist40,
	dist50,
	dist60,
	dist70,
	dist80,
	dist90,
	dist100,
	distN,
} ultrasound_distances_t;

bool ultrasound_init(void);

/*
 * need to waits 10us
 */
void ultrasound_trig(void);

void timer_ultrasound_sensor_tigger(TimerHandle_t xTimer);

uint16_t ultrasound_select_proper_distance(uint8_t code);

#endif /* APPLICATION_MODULES_ULTRASOUND_SENSOR_ULTRASOUND_H_ */
