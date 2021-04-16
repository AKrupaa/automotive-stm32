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
	EventGroupHandle_t Evh = g_rt_evgroups[Ev];

	return xEventGroupWaitBits(Evh, 0x00FFFFFFu, pdTRUE, pdFALSE, portMAX_DELAY);
}

void rt_evbit_set(rt_evgroup_t Ev, uint32_t bit) {
	EventBits_t msk = (1u << bit);
	xEventGroupSetBits(Evh, msk);
}

void rt_evbit_set_from_ISR(rt_evgroup_t Ev, uint32_t bit) {
	EventBits_t msk = (1u << bit);
	xEventGroupSetBitsFromISR(Evh, msk, pdFALSE);
	portYIELD_FROM_ISR(pdFALSE);
}
