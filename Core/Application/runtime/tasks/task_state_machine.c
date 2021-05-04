/*
 * state_machine_task.c
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

//#include "task_state_machine.h"
#include "runtime.h"
#include "state_machine.h"
#include "h_bridge.h"
#include "bluetooth_le.h"

void task_state_machine(void *pvParameters) {

	(void*) pvParameters;

	uint32_t evgroup = 0;
	bool tasks_disabled = false;
	xQueueBleData receivedBleData = { 0 };

	for (;;) {

		evgroup = rt_evbitwait_any(rt_evgroup_state_machine);

		if (evgroup & (1 << evgroup_state_m_do_nothing)) {

			h_bridge_coast();
			h_bridge_set_left_duty(0);
			h_bridge_set_right_duty(0);
		}
		if (evgroup & (1 << evgroup_state_m_auto_manual)) {
			if (tasks_disabled) {
				vTaskResume(rt_tasks[rt_task_eyes]);
				vTaskResume(rt_tasks[rt_task_memory]);
				vTaskResume(rt_tasks[rt_task_sensors]);
			} else {
				vTaskSuspend(rt_tasks[rt_task_eyes]);
				vTaskSuspend(rt_tasks[rt_task_memory]);
				vTaskSuspend(rt_tasks[rt_task_sensors]);
			}
		}
		if (evgroup & (1 << evgroup_state_m_movement)) {

			bool status = rt_dequeue(rt_queue_ble, &receivedBleData);
			if (status) {

				uint8_t left_engine = receivedBleData.valueReg1;
				uint8_t right_engine = receivedBleData.valueReg2;

				// 1	1	1	0	0	1	0	0
				// ^
				// cw

				// 0	1	1	0	0	1	0	0
				// ^
				// ccw
				// --- |        PERCENTAGE       |

				// left engine
				if (left_engine & (1 << 8)) {
					h_bridge_cw_left();
					h_bridge_set_left_duty(left_engine & 0b01111111);
				} else {
					h_bridge_ccw_left();
					h_bridge_set_left_duty(right_engine & 0b01111111);
				}

				// right engine
				if (right_engine & (1 << 8)) {
					h_bridge_cw_right();
					h_bridge_set_right_duty(right_engine & 0b01111111);
				} else {
					h_bridge_ccw_right();
					h_bridge_set_right_duty(right_engine & 0b01111111);
				}
			}
		}
	}
}
