/*
 * runtime.h
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_RUNTIME_RUNTIME_H_
#define APPLICATION_RUNTIME_RUNTIME_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdatomic.h>

#include "stm32l1xx_hal.h"

#include "runtime_conf.h"

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "queue.h"

typedef struct rt_task_definition {
	TaskFunction_t pvTaskCode;
	const char *pcName;
	void *pvParameters;
	UBaseType_t uxPriority;
	uint16_t usStackDepth;
//	TaskHandle_t *pxCreatedTask;
	bool active;
} rt_task_def_t;


typedef struct rt_queue_definition {
	UBaseType_t uxQueueLength;
	UBaseType_t uxItemSize;
} rt_queue_def_t;

//struct rt_evgroup_def {
//  TickType_t timeout;
//  bool critical;
//};

typedef struct rt_timer_definition {
	char const *pcTimerName;
	uint32_t xTimerPeriodInTicks;
	UBaseType_t uxAutoReload;
	TimerCallbackFunction_t pxCallbackFunction;
} rt_timer_def_t;


/***********************************************/
/* definitons are included in runtime_conf.c */
extern const rt_task_def_t rt_task_def[rt_task_N];
extern const rt_queue_def_t rt_queue_def[rt_queue_N];
extern const rt_timer_def_t rt_timer_def[rt_timer_N];

/* def are included in runtime.c */
extern TaskHandle_t rt_tasks[rt_task_N];
extern QueueHandle_t rt_queues[rt_queue_N];
extern EventGroupHandle_t rt_evgroups[rt_evgroup_N];
extern TimerHandle_t rt_timers[rt_timer_N];

void rt_init(void);
uint32_t rt_evbitwait_any(rt_evgroup_t Ev);
void rt_evbit_set(rt_evgroup_t Ev, uint32_t bit);
void rt_evbit_set_from_ISR(rt_evgroup_t Ev, uint32_t bit);

#endif /* APPLICATION_RUNTIME_RUNTIME_H_ */
