/*
 * task_sensors.c
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

//#include "task_sensors.h"
#include "h_bridge.h"
#include "hall.h"
#include "magnetometer.h"
#include "servo/servo.h"
#include "slotted_optocoupler/optocoupler.h"
#include "ultrasound_sensor/ultrasound.h"
#include "stdbool.h"
#include "runtime.h"

static uint32_t ultrasound_time = 0U;
bool ultrasound_was = false;
bool ultrasound_done = false;

// interrupt pin callback
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//	IRQ_ULTRASOUND_ECHO_Pin
	if (GPIO_Pin & (1 << IRQ_ULTRASOUND_ECHO_Pin)) {

		if (ultrasound_was == false) {
			ultrasound_time = HAL_GetTick();
			ultrasound_was = true;
		} else {
			ultrasound_timer = HAL_GetTick() - ultrasound_timer;
			ultrasound_was = false;
			rt_evbit_set_from_ISR(rt_evgroup_sensors,
					evgroup_ultrasound_evbit_echo);
//			ultrasound_done = true;
		}
	}
}

void task_sensors(void *pvParameters) {
	(void*) pvParameters;

	uint32_t evgroup = 0;

	for (;;) {
		// ultrasound measurment
//		ultrasound_trig();
//		if ( ultrasound_done ) {

//		}

		evgroup = rt_evbitwait_any(rt_evgroup_sensors);

		if (evgroup & (1 << evgroup_ultrasound_evbit_echo)) {
			// obsluga sensora ultradzwiekowego
			// policz odleglosc
			// na podstawie na danych zareaguj :)
		}

	}

}
