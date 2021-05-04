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
uint8_t pData[BLE_MAX_SIZE];
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
		BaseType_t pxHigherPriorityTaskWoken = pdFALSE;

//		ble_receive_data(pData);
		pxHigherPriorityTaskWoken = pdTRUE;
		rt_timer_start_ISR(rt_timer_BLE, &pxHigherPriorityTaskWoken);
//			xTimerStartFromISR(rt_timers[T], pxHigherPriorityTaskWoken);

	}
}

void task_sensors(void *pvParameters) {
	(void*) pvParameters;

//	uint32_t evgroup = 0;

// TODO: delete this line!
//	magnetometer_init();
	QMC5883L_Initialize(MODE_CONTROL_CONTINUOUS, OUTPUT_DATA_RATE_200HZ,
			FULL_SCALE_2G, OVER_SAMPLE_RATIO_128);
	QMC5883L_InterruptConfig(INTERRUPT_DISABLE);

	//Mode Register
	//Continuous-Measurement Mode
	QMC5883L_Write_Reg(0x02, 0x00);

	for (;;) {
		// ultrasound measurment
//		ultrasound_trig();
//		if ( ultrasound_done ) {
//		}

//		evgroup = rt_evbitwait_any(rt_evgroup_sensors);

//		if (evgroup & (1 << evgroup_ultrasound_evbit_echo)) {
		// obsluga sensora ultradzwiekowego
		// policz odleglosc
		// na podstawie na danych zareaguj :)

		// jakis tam bit do ustawienia, np skret w lewo - uzupelnic
//			rt_evbit_set(rt_evgroup_state_machine, (1 << 8));
//		}
		int16_t X = 0;
		int16_t Y = 0;
		int16_t Z = 0;

		uint8_t status = QMC5883L_Read_Reg(0x09);
		uint8_t temp1 = 0;
		uint8_t temp2 = 0;

		temp1 = QMC5883L_Read_Reg(0x07);
		temp2 = QMC5883L_Read_Reg(0x08);

		uint16_t temp = ~((temp2 << 8) | temp1) + 1;
		temp /= 100;

		temp += 1;

		if (status & (1 << 0)) {
			QMC5883L_Read_Data(&X, &Y, &Z);
		} else {
			X = 0;
			Y = 0;
			Z = 0;
		}

		X++;

//		if (NORMAL == QMC5883L_DataIsReady()) {
//		temperature = QMC5883L_Read_Temperature();
//		temperature /= 10;
//		}

	}

}
