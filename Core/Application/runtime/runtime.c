/*
 * runtime.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#include "runtime.h"

TaskHandle_t rt_tasks[rt_task_N];
QueueHandle_t rt_queues[rt_queue_N];
EventGroupHandle_t rt_evgroups[rt_evgroup_N];
TimerHandle_t rt_timers[rt_timer_N];

void rt_init(void) {

	for (rt_task_t task = rt_task_0; task < rt_task_N; task++) {
		rt_task_def_t const *def = rt_task_def + task;
		TaskHandle_t *handle = rt_tasks + task;
		if (def->active) {
			if (xTaskCreate(def->pvTaskCode, def->pcName, def->usStackDepth,
					def->pvParameters, def->uxPriority, handle) != pdPASS) {
//				error :-(
				while (1)
					;
			}
		} else {
			*handle = 0;
		}
	}

	for (rt_queue_t queue = rt_queue_0; queue < rt_queue_N; queue++) {
		rt_queue_def_t const *def = rt_queue_def + queue;
		QueueHandle_t *handle = rt_queues + queue;

		if ((*handle = xQueueCreate(def->uxQueueLength, def->uxItemSize))
				== 0) {
			while (1)
				;
		}
	}

	for (rt_timer_t timer = rt_timer_0; timer < rt_timer_N; timer++) {
		rt_timer_def_t const *def = rt_timer_def + timer;
		TimerHandle_t *handle = rt_timers + timer;

		if ((*handle = xTimerCreate(def->pcTimerName, def->xTimerPeriodInTicks,
				def->uxAutoReload, NULL, def->pxCallbackFunction)) == 0)
			while (1)
				;
	}

	for (rt_evgroup_t evgroup = rt_evgroup_0; evgroup < rt_evgroup_N;
			evgroup++) {
		EventGroupHandle_t *handle = rt_evgroups + evgroup;

		if ((*handle = xEventGroupCreate()) == 0) {
			while (1)
				;
		}
	}

}

uint32_t rt_evbitwait_any(rt_evgroup_t Ev) {
	EventGroupHandle_t Evh = rt_evgroups[Ev];

	return xEventGroupWaitBits(Evh, 0x00FFFFFFu, pdTRUE, pdFALSE, portMAX_DELAY);
}

uint32_t rt_evbitcheck_any(rt_evgroup_t Ev) {
	EventGroupHandle_t Evh = rt_evgroups[Ev];

	return xEventGroupWaitBits(Evh, 0x00FFFFFFu, pdFALSE, pdFALSE, 0);
}

uint32_t rt_evbitclear(rt_evgroup_t Ev, uint32_t bits_to_clear) {
	EventGroupHandle_t Evh = rt_evgroups[Ev];

//	uxBits =

	return xEventGroupClearBits(Evh, // The event group being updated.
			bits_to_clear);	// The bits being cleared.
}

BaseType_t rt_evbitclear_ISR( rt_evgroup_t Ev, uint32_t bits_to_clear) {
	EventGroupHandle_t Evh = rt_evgroups[Ev];


	return xEventGroupClearBitsFromISR(Evh, // The event group being updated.
			bits_to_clear);	// The bits being cleared.
}

void rt_evbit_set(rt_evgroup_t Ev, uint32_t bit) {
	EventBits_t msk = (1u << bit);
	EventGroupHandle_t Evh = rt_evgroups[Ev];
	xEventGroupSetBits(Evh, msk);
}

void rt_evbit_set_from_ISR(rt_evgroup_t Ev, uint32_t bit) {
	EventBits_t msk = (1u << bit);
	EventGroupHandle_t Evh = rt_evgroups[Ev];
	xEventGroupSetBitsFromISR(Evh, msk, pdFALSE);
	portYIELD_FROM_ISR(pdFALSE);
}

bool rt_enqueue(rt_queue_t Q, void const *bf) {
//  assert(Q < rt_queue_N);

	QueueHandle_t Qh = rt_queues[Q];
	TickType_t to = rt_queue_def[Q].timeout_enq;

	if (xQueueSendToBack(Qh, bf, to) == pdPASS) {
		return true;
	}

	return false;
}

bool rt_enqueue_ISR(rt_queue_t Q, void const *bf) {
//  assert(Q < rt_queue_N);

	QueueHandle_t Qh = rt_queues[Q];
	BaseType_t xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	if (xQueueSendToBackFromISR(Qh, bf, &xHigherPriorityTaskWoken) == pdPASS) {
		return true;
	}

	return false;
}

bool rt_dequeue(rt_queue_t Q, void *bf) {
//  assert(Q < rt_queue_N);

	QueueHandle_t Qh = rt_queues[Q];
	TickType_t to = rt_queue_def[Q].timeout_deq;

	if (xQueueReceive(Qh, bf, to) == pdPASS) {
		return true;
	}

	return false;
}

bool rt_queue_peek(rt_queue_t Q, void *bf) {

	QueueHandle_t Qh = rt_queues[Q];

	if (xQueuePeek(Qh, bf, pdMS_TO_TICKS(portMAX_DELAY)) == pdPASS) {
		return true;
	}

	return false;
}

bool rt_timer_start(rt_timer_t t, uint32_t timeout) {
	return xTimerStart(rt_timers[t], timeout);
}

bool rt_timer_start_ISR(rt_timer_t t, BaseType_t *pxHigherPriorityTaskWoken) {
	return xTimerStartFromISR(rt_timers[t], pxHigherPriorityTaskWoken);
}
