/*
 * state_machine_task.c
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

//#include "task_state_machine.h"
#include "runtime.h"
#define jakis_tam_bit 12
void task_state_machine(void *pvParameters) {

	(void*) pvParameters;

	uint32_t evgroup = 0;

	for (;;) {

		evgroup = rt_evbitwait_any(rt_evgroup_sensors);

		if (evgroup & (1 << jakis_tam_bit)) {
			;
			// np obsluga skretu w lewo
		}
		if (evgroup & (1 << jakis_tam_bit)) {
			;
			// np obsluga skretu w prawo
		}
		if (evgroup & (1 << jakis_tam_bit)) {
			;
			// np mozna prosto?
		}
		if (evgroup & (1 << jakis_tam_bit)) {
			;
			// np obsluga czegos tam
		}
	}
}
