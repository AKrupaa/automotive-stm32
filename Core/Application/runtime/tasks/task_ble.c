/*
 * task_ble.c
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

//#include "task_ble.h"
#include "bluetooth_le.h"
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
				memset(ble_pData, 0, MAX_SIZE);

				switch(ble_pData[0]) {
//				case 1 << 0
				}

			}

			if (receivedBleData.info == ble_transmit) {
//				ble_pData = receivedBleData.value;

			}
		}

	}

}
