/*
 * task_sensors.c
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

//#include "task_sensors.h"
#include "h_bridge.h"
#include "hall.h"
#include "magnetometer.h"
#include "servo/servo.h"
#include "slotted_optocoupler/optocoupler.h"
#include "ultrasound_sensor/ultrasound.h"
#include "bluetooth_le.h"
#include "stdbool.h"
#include "runtime.h"

static uint32_t ultrasound_time = 0U;
bool ultrasound_was = false;
bool ultrasound_done = false;
extern char ble_pData[MAX_SIZE];

// interrupt pin callback
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//	IRQ_ULTRASOUND_ECHO_Pin
	if (GPIO_Pin & IRQ_ULTRASOUND_ECHO_Pin) {

		if (ultrasound_was == false) {
			ultrasound_time = HAL_GetTick();
			ultrasound_was = true;
		} else {
			ultrasound_time = HAL_GetTick() - ultrasound_time;
			ultrasound_was = false;
			rt_evbit_set_from_ISR(rt_evgroup_sensors,
					evgroup_ultrasound_evbit_echo);
//			ultrasound_done = true;
		}
	}

//	BLE INTERRUPT -> SOMETHING IS RECEIVED
	if (GPIO_Pin & IRQ_BLE_Pin) {
//		rt_evbit_set_from_ISR(rt_evgroup_ble, evgroup_ble_evbit_received);
		ble_receive_data(ble_pData);
		xQueueBleData ble_queue = { 0 };
		strncpy(ble_queue.value, ble_pData, MAX_SIZE);
		ble_queue.info = ble_received;

		rt_enqueue_ISR(rt_queue_ble, &ble_queue);
//		memset(ble_pData, 0, MAX_SIZE);
	}
}

void task_sensors(void *pvParameters) {
	(void*) pvParameters;

	uint32_t evgroup = 0;

	for (;;) {
		// ultrasound measurment
//		ultrasound_trig();
//		if ( ultrasound_done ) {
//		}

		evgroup = rt_evbitwait_any(rt_evgroup_sensors);

		if (evgroup & (1 << evgroup_ultrasound_evbit_echo)) {
			// obsluga sensora ultradzwiekowego
			// policz odleglosc
			// na podstawie na danych zareaguj :)

			// jakis tam bit do ustawienia, np skret w lewo - uzupelnic
			rt_evbit_set(rt_evgroup_state_machine, (1 << 8));
		}

	}

}
