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
#include "ultrasound.h"
uint16_t ULTRASOUND_PROPER_DISTANCE_u16;
char ble_pData[BLE_MAX_SIZE];
char ble_pDataSend[BLE_MAX_SIZE];
int temp = 0;
// works only when BLE receive something -> void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
// working all the time, checking if something is received or sending data to android device

/* ************************************************************************** */
// callback
/* ************************************************************************** */
void timer_BLE(TimerHandle_t xTimer) {
	HAL_UART_Receive_DMA(&huart3, (uint8_t*) ble_pData, BLE_MAX_SIZE);
}

// auto-reload - triggering temperature measurement inside MCU
//void timer_trigger_temperature_measurement(TimerHandle_t xTimer) {
//	HAL_ADC_ST
//
//
//	ble_pDataSend[0] = 0x01;
//
//	ble_pDataSend[2] = 0x03;
//
//	if (temp++ == 1) {
//		ble_pDataSend[1] = 0x02;
//		ble_pDataSend[2] = 0xBC;
//		temp = 0;
//	} else {
//		ble_pDataSend[1] = 0x01;
//		ble_pDataSend[2] = 0xAA;
//	}
//	xQueueBleData toBeTransmit_ble_pData = { 0 };
//
//	toBeTransmit_ble_pData.info = ble_transmit;
//	toBeTransmit_ble_pData.command = 0x00;
//	toBeTransmit_ble_pData.valueReg1 = ble_pDataSend[1];
//	toBeTransmit_ble_pData.valueReg2 = ble_pDataSend[2];
//
//	rt_enqueue_ISR(rt_queue_ble, &toBeTransmit_ble_pData);
//
//	HAL_UART_Transmit_DMA(&huart3, (uint8_t*) ble_pDataSend, BLE_MAX_SIZE);
//
//
//}
//
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	__NOP();
}

void HAL_UART_TxHalfCallback(UART_HandleTypeDef *huart) {
	__NOP();
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

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
	__NOP();
}

/* ************************************************************************** */
// task
/* ************************************************************************** */
void task_ble(void *pvParameters) {
	(void*) pvParameters;

	bool status;
	xQueueBleData receivedBleData = { 0 };
//	char ble_pData[BLE_MAX_SIZE] = { 0 };
	uint8_t left_engine;
	uint8_t right_engine;
	uint16_t whichOne;

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
						// allowed to drive forward?
						uint32_t evbits = rt_evbit_check_any(
								rt_evgroup_ultrasound);
						if (evbits & (1 << evgroup_ultrasound_evbit_move)) {
							// yes
							h_bridge_cw_left();
							h_bridge_set_left_duty(left);
						} else {
							h_bridge_stop();
							h_bridge_set_left_duty(0);
						}

					}

					// right engine
					if (right < 0) {
						h_bridge_ccw_right();
						h_bridge_set_right_duty(-right);
					} else {
						// allowed to drive forward?
						uint32_t evbits = rt_evbit_check_any(
								rt_evgroup_ultrasound);
						if (evbits & (1 << evgroup_ultrasound_evbit_move)) {
							// yes
							h_bridge_cw_right();
							h_bridge_set_right_duty(right);
						} else {
							h_bridge_stop();
							h_bridge_set_right_duty(0);
						}
					}
					break;

				case BLE_RECEIVED_ULTRASOUND_CONFIG:

					whichOne = receivedBleData.valueReg2;

					ULTRASOUND_PROPER_DISTANCE_u16 = ultrasound_select_proper_distance(whichOne);

					break;
				default:
					// unknow -> free
					rt_dequeue(rt_queue_ble, &receivedBleData);
					break;
				}

			}

			if (receivedBleData.info == ble_transmit) {

				memcpy(ble_pDataSend, &receivedBleData.command, 1);
				memcpy(ble_pDataSend + 1, &receivedBleData.valueReg1, 1);
				memcpy(ble_pDataSend + 2, &receivedBleData.valueReg2, 1);

				HAL_UART_Transmit(&huart3, (uint8_t*) ble_pDataSend,
				BLE_MAX_SIZE, 1);

//				HAL_UART_Transmit_DMA(&huart3, (uint8_t*) ble_pDataSend, BLE_MAX_SIZE);
			}
		}

	}

}
