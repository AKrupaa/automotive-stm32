/*
 * runtime_conf.h
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_RUNTIME_RUNTIME_CONF_H_
#define APPLICATION_RUNTIME_RUNTIME_CONF_H_
#include "FreeRTOS.h"
#include "task.h"

/// RTOS tasks.
typedef enum rt_task {
	rt_task_0,
	rt_task_ble = rt_task_0,
	rt_task_eyes,
	rt_task_memory,
	rt_task_sensors,
	rt_task_state_machine,
	rt_task_N
} rt_task_t;


/// RTOS queues.
typedef enum rt_queue {
	rt_queue_0,
	rt_queue_cos_tam = rt_queue_0,
	rt_queue_cos_tam_2,
	rt_queue_N
} rt_queue_t;

/// RTOS event groups.
typedef enum rt_evgroup {
	rt_evgroup_0,
	rt_evgroup_cos_tam = rt_evgroup_0,
	rt_evgroup_cos_tam2,
	rt_evgroup_N
} rt_evgroup_t;

/// RTOS event groups.
typedef enum rt_timer {
	rt_timer_0,
	rt_timer_blabla = rt_timer_0,
	rt_timer_blabla2,
	rt_timer_N
} rt_timer_t;


portTASK_FUNCTION_PROTO(task_ble, unused);
portTASK_FUNCTION_PROTO(task_eyes, unused);
portTASK_FUNCTION_PROTO(task_memory, unused);
portTASK_FUNCTION_PROTO(task_sensors, unused);
portTASK_FUNCTION_PROTO(task_state_machine, unused);

#endif /* APPLICATION_RUNTIME_RUNTIME_CONF_H_ */