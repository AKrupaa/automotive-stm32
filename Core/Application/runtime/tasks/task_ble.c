/*
 * task_ble.c
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

//#include "task_ble.h"
#include "bluetooth_le.h"
#include "state_machine.h"
#include "main.h"
#include <stdio.h>
char ble_pData[BLE_MAX_SIZE];
// working all the time, checking if something is received or sending data to android device

/* ************************************************************************** */
// callback
/* ************************************************************************** */
void timer_BLE(TimerHandle_t xTimer) {

	HAL_UART_Receive_DMA(&huart3, (uint8_t*) ble_pData, sizeof(ble_pData) -1);

//	char ble_pData[BLE_MAX_SIZE];
//	memset(ble_pData, 1, BLE_MAX_SIZE);
//	ble_receive_data(ble_pData);
//	xQueueBleData ble_queue = { 0 };
//
//	ble_queue.info = ble_received;
//
//	memcpy(&ble_queue.command, ble_pData, 1);
//	memcpy(&ble_queue.valueReg1, ble_pData + 1, 1);
//	memcpy(&ble_queue.valueReg2, ble_pData + 2, 1);
//
//	rt_enqueue_ISR(rt_queue_ble, &ble_queue);

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	__NOP();
//	char ble_pData[BLE_MAX_SIZE];
	memset(ble_pData, 1, BLE_MAX_SIZE);
	ble_receive_data(ble_pData);
	xQueueBleData ble_queue = { 0 };

	ble_queue.info = ble_received;

	memcpy(&ble_queue.command, ble_pData, 1);
	memcpy(&ble_queue.valueReg1, ble_pData + 1, 1);
	memcpy(&ble_queue.valueReg2, ble_pData + 2, 1);

	rt_enqueue_ISR(rt_queue_ble, &ble_queue);

}
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart) {
	__NOP();
}

void task_ble(void *pvParameters) {
	(void*) pvParameters;

//	int i = 0;
//	const TickType_t xDelay1000ms = pdMS_TO_TICKS(5000);
	bool status;
	xQueueBleData receivedBleData = { 0 };
	char ble_pData[BLE_MAX_SIZE] = { 0 };
	for (;;) {

//		vTaskDelay(xDelay1000ms);

		status = rt_queue_peek(rt_queue_ble, &receivedBleData);

		if (status) {
			if (receivedBleData.info == ble_received) {
//				memcpy(ble_pData, receivedBleData.value, BLE_MAX_SIZE);

				switch (receivedBleData.command) {
				case BLE_RECEIVED_DO_NOTHING:
					rt_evbit_set(rt_evgroup_state_machine,
							evgroup_state_m_do_nothing);
					break;
				case BLE_RECEIVED_AUTO_MANUAL:
					rt_evbit_set(rt_evgroup_state_machine,
							evgroup_state_m_auto_manual);
					break;
				case BLE_RECEIVED_MOVEMENT:
					rt_evbit_set(rt_evgroup_state_machine,
							evgroup_state_m_movement);
					break;
				default:
					// unknow -> free
					rt_dequeue(rt_queue_ble, &receivedBleData);
					break;
				}

			}

			if (receivedBleData.info == ble_transmit) {

//				memcpy(ble_pData, data + sizeof(Śmieci),4);

				memcpy(ble_pData, &receivedBleData.command, 1);
				memcpy(ble_pData + 1, &receivedBleData.valueReg1, 1);
				memcpy(ble_pData + 2, &receivedBleData.valueReg2, 1);
//				memcpy(ble_pData + 3, &receivedBleData.valueReg3, 1);
//				memcpy(ble_pData + 4, &receivedBleData.valueReg4, 1);

				ble_send_data(ble_pData, BLE_MAX_SIZE);

//				memset (ble_pData, )
//				ble_pData = receivedBleData.value;
//				memset(ble_pData, 0, BLE_MAX_SIZE);
//				strncpy(receivedBleData.value, ble_pData, MAX_SIZE);
//				strncpy(ble_pData, receivedBleData.value, BLE_MAX_SIZE);
//				ble_send_data(ble_pData);
			}
		}

	}

}
