/*
 * task_memory.c
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

//#include "task_memory.h"

#include "FreeRTOS.h"
#include "task.h"
#include "runtime.h"
void task_memory(void *pvParameters) {

	(void*) pvParameters;
	rt_timer_start(rt_timer_jakis_tam, 300);
	for (;;) {
//		vTaskDelay(pdMS_TO_TICKS(1000));

	}

}
