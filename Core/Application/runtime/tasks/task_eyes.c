/*
 * eyes.c
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

//#include "task_eyes.h"
#include "FreeRTOS.h"
#include "task.h"
#include "runtime.h"

/* ************************************************************************** */
// callback
/* ************************************************************************** */
void timer_ultrasound_sensor_tigger(TimerHandle_t xTimer) {
//	HAL_UART_Receive_DMA(&huart3, (uint8_t*) ble_pData, BLE_MAX_SIZE);
}

void task_eyes(void *pvParameters) {

//	rt_timer_start(rt_timer_ultrasound_sensor_trigger, timeout)

	(void*) pvParameters;

	for (;;) {

		taskYIELD();
	}

}
