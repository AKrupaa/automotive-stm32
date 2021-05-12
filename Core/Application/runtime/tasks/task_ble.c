/*
 * task_ble.c
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

//#include "task_ble.h"
#include "bluetooth_le.h"
#include "state_machine.h"
#include "h_bridge.h"
#include "main.h"
#include <stdio.h>
#include "utility.h"
char ble_pData[BLE_MAX_SIZE];
// works only when BLE receive something -> void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
// working all the time, checking if something is received or sending data to android device

/* ************************************************************************** */
// callback
/* ************************************************************************** */
void timer_BLE(TimerHandle_t xTimer) {
	HAL_UART_Receive_DMA(&huart3, (uint8_t*) ble_pData, BLE_MAX_SIZE);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//	__NOP();
//	char ble_pData[BLE_MAX_SIZE];
//	memset(ble_pData, 1, BLE_MAX_SIZE);
//	ble_receive_data(ble_pData);
	xQueueBleData ble_queue = { 0 };

	ble_queue.info = ble_received;

	memcpy(&ble_queue.command, ble_pData, 1);
	memcpy(&ble_queue.valueReg1, ble_pData + 1, 1);
	memcpy(&ble_queue.valueReg2, ble_pData + 2, 1);

	rt_enqueue_ISR(rt_queue_ble, &ble_queue);

}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);/* {
 __NOP();
 }*/

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart);

/* ************************************************************************** */
// task
/* ************************************************************************** */
void task_ble(void *pvParameters) {
	(void*) pvParameters;

//	int i = 0;
//	const TickType_t xDelay1000ms = pdMS_TO_TICKS(5000);
	bool status;
	xQueueBleData receivedBleData = { 0 };
	char ble_pData[BLE_MAX_SIZE] = { 0 };
	uint8_t left_engine;
	uint8_t right_engine;
	for (;;) {

//		vTaskDelay(xDelay1000ms);

		status = rt_dequeue(rt_queue_ble, &receivedBleData);

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
//					rt_evbit_set(rt_evgroup_state_machine,
//							evgroup_state_m_movement);

					left_engine = receivedBleData.valueReg1;
					right_engine = receivedBleData.valueReg2;

					// 1	1	1	0	0	1	0	0
					// ^
					// cw

					// 0	1	1	0	0	1	0	0
					// ^
					// ccw
					// --- |        PERCENTAGE       |

					int left = u2_to_decimal(left_engine);
					int right = u2_to_decimal(right_engine);

					// left engine
					if (left < 0) {
						h_bridge_ccw_left();
						h_bridge_set_left_duty(-left);
					} else {
						h_bridge_cw_left();
						h_bridge_set_left_duty(left);
					}

					// right engine
					if (right < 0) {
						h_bridge_ccw_right();
						h_bridge_set_right_duty(-right);
					} else {
						h_bridge_cw_right();
						h_bridge_set_right_duty(right);
					}

					break;
				default:
					// unknow -> free
					rt_dequeue(rt_queue_ble, &receivedBleData);
					break;
				}

			}

			if (receivedBleData.info == ble_transmit) {

//				rt_dequeue(rt_queue_ble, &receivedBleData);
				memcpy(ble_pData, &receivedBleData.command, 1);
				memcpy(ble_pData + 1, &receivedBleData.valueReg1, 1);
				memcpy(ble_pData + 2, &receivedBleData.valueReg2, 1);

//				ble_send_data(ble_pData, BLE_MAX_SIZE);
				HAL_UART_Transmit_DMA(&huart3, (uint8_t*) ble_pData,
				BLE_MAX_SIZE);

			}
		}

	}

}
