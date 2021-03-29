/*
 * runtime_conf.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#include "runtime.h"
#include "runtime_conf.h"
//#include "task_ble.h"
//#include "task_eyes.h"
//#include "task_memory.h"
//#include "task_sensors.h"
//#include "task_state_machine.h"

rt_task_def_t const rt_task_def[rt_task_N] = {
		{
				.pvTaskCode = task_ble,
				.pcName = "BLUETOOTH LOW ENERGY TASK",
				.pvParameters = NULL,
				.usStackDepth = 5u * configMINIMAL_STACK_SIZE,
				.uxPriority = 2u,
				.active = true
		},
		{
				.pvTaskCode = task_eyes,
				.pcName = "EYES TAKS",
				.pvParameters = NULL,
				.usStackDepth = 5u * configMINIMAL_STACK_SIZE,
				.uxPriority = 2u,
				.active = true
		},
		{
				.pvTaskCode = task_memory,
				.pcName = "MEMORY TASK",
				.pvParameters = NULL,
				.usStackDepth = 5u * configMINIMAL_STACK_SIZE,
				.uxPriority = 2u,
				.active = true
		},
		{
				.pvTaskCode = task_sensors,
				.pcName = "SENSORS TASK",
				.pvParameters = NULL,
				.usStackDepth = 5u * configMINIMAL_STACK_SIZE,
				.uxPriority = 2u,
				.active = true
		},
		{
				.pvTaskCode = task_state_machine,
				.pcName = "STATE MACHINE",
				.pvParameters = NULL,
				.usStackDepth = 5u * configMINIMAL_STACK_SIZE,
				.uxPriority = 2u,
				.active = true
		},
};


rt_queue_def_t const rt_queue_def[rt_queue_N] = {
		{
				.uxQueueLength = 5,
				.uxItemSize = sizeof(int) /* insert here your size */
		},
		{
				.uxQueueLength = 5,
				.uxItemSize = sizeof(float) /* insert here your size */
		},
};


//rt_evgroup_t const rt_event_def[rt_event]

rt_timer_def_t const rt_timer_def[rt_queue_N] = {
		{
				.pxCallbackFunction = "wskaznik na funckje jakas tam",
				.pcTimerName = "jakas nazwa",
				.uxAutoReload = true,
				.xTimerPeriodInTicks = pdMS_TO_TICKS(10)
		},
		{
				.pxCallbackFunction = "wskaznik na funckje jakas tam2",
				.pcTimerName = "jakas nazwa2",
				.uxAutoReload = true,
				.xTimerPeriodInTicks = pdMS_TO_TICKS(20)
		},
};


//typedef struct xd{
//	char b;
//	int a;
//} __attribute__((packed)) xde;