/*
 * task_ble.c
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

//#include "task_ble.h"
#include "bluetooth_le.h"
#include "state_machine.h"
#include <stdio.h>
extern char ble_pData[MAX_SIZE];
// working all the time, checking if something is received or sending data to android device
void task_ble(void *pvParameters) {
	(void*) pvParameters;

//	int i = 0;
//	const TickType_t xDelay1000ms = pdMS_TO_TICKS(5000);
	bool status;
	xQueueBleData receivedBleData = { 0 };
	for (;;) {

//		vTaskDelay(xDelay1000ms);

		status = rt_dequeue(rt_queue_ble, &receivedBleData);

		if (status) {
			if (receivedBleData.info == ble_received) {
				memcpy(ble_pData, receivedBleData.value, MAX_SIZE);

				switch (ble_pData[0]) {
				case BLE_RECEIVED_DO_NOTHING:
					rt_evbit_set(rt_evgroup_state_machine,
							evgroup_state_m_do_nothing);
					break;
				case BLE_RECEIVED_AUTO_MANUAL:
					rt_evbit_set(rt_evgroup_state_machine,
							evgroup_state_m_auto_manual);
					break;
				case BLE_RECEIVED_RIGHT:
					rt_evbit_set(rt_evgroup_state_machine,
							evgroup_state_m_right);
					break;
				case BLE_RECEIVED_FORWARD:
					rt_evbit_set(rt_evgroup_state_machine,
							evgroup_state_m_forward);
					break;
				case BLE_RECEIVED_LEFT:
					rt_evbit_set(rt_evgroup_state_machine,
							evgroup_state_m_left);
					break;
				case BLE_RECEIVED_BACK:
					rt_evbit_set(rt_evgroup_state_machine,
							evgroup_state_m_back);
					break;
				default:
					memset(ble_pData, 0, MAX_SIZE);
					break;
				}

			}

			if (receivedBleData.info == ble_transmit) {
//				ble_pData = receivedBleData.value;
				memset(ble_pData, 0, MAX_SIZE);
//				strncpy(receivedBleData.value, ble_pData, MAX_SIZE);
				strncpy(ble_pData, receivedBleData.value, MAX_SIZE);
				ble_send_data(ble_pData);
			}
		}

	}

}
