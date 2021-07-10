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
#include "temperature_measurement.h"
#include "bluetooth_le.h"
#include "stdbool.h"
#include "runtime.h"
#include "adc.h"
#include "tim.h"
#include "utility.h"

union {
	uint32_t uint32;
	uint16_t uint16[2];
	uint8_t uint8[4];
} type_casting;

//static uint32_t ultrasound_time = 0U;
bool ultrasound_was = false;
//bool ultrasound_done = false;
uint8_t pData[BLE_MAX_SIZE];
extern char temperature_measurement[SIZE_OF_TEMPERATURE_MEASURMENT_ARRAY];
void TIM_ResetCounter(TIM_TypeDef *TIMx) {
	/* Check the parameters */
	assert_param(IS_TIM_ALL_PERIPH(TIMx));

	/* Reset the Counter Register value */
	TIMx->CNT = 0;
}
// interrupt pin callback
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//	IRQ_ULTRASOUND_ECHO_Pin
	if (GPIO_Pin & IRQ_ULTRASOUND_ECHO_Pin) {

		if (HAL_GPIO_ReadPin(IRQ_ULTRASOUND_ECHO_GPIO_Port,
		IRQ_ULTRASOUND_ECHO_Pin)) {

//			__HAL_TIM_SET_COUNTER(&htim4, 0);

//			HAL_TIM_Base_Start(&htim4);
			ultrasound_was = true;
		} else {
			HAL_TIM_Base_Stop(&htim4);
			uint16_t count = __HAL_TIM_GET_COUNTER(&htim4);
			ultrasound_was = false;

			/// 	clear 	(if > 30 cm) 	==> 	allowed to drive forward
			/// 	set 	(if < 30 cm) 	==> 	forbidden to drive forward
			if (count > (uint16_t) ULTRASOUND_DIST_40CM_BITS) {
				rt_evbit_clear_ISR(rt_evgroup_ultrasound,
						evgroup_ultrasound_evbit_move);
			} else if (count > (uint16_t) ULTRASOUND_DIST_35CM_BITS) {
				rt_evbit_clear_ISR(rt_evgroup_ultrasound,
						evgroup_ultrasound_evbit_move);
			} else if (count > (uint16_t) ULTRASOUND_DIST_30CM_BITS) {
				rt_evbit_clear_ISR(rt_evgroup_ultrasound,
						evgroup_ultrasound_evbit_move);
			} else if (count > (uint16_t) ULTRASOUND_DIST_25CM_BITS) {
				rt_evbit_set_ISR(rt_evgroup_ultrasound,
						evgroup_ultrasound_evbit_move);
			} else if (count > (uint16_t) ULTRASOUND_DIST_20CM_BITS) {
				rt_evbit_set_ISR(rt_evgroup_ultrasound,
						evgroup_ultrasound_evbit_move);
			} else if (count > (uint16_t) ULTRASOUND_DIST_15CM_BITS) {
				rt_evbit_set_ISR(rt_evgroup_ultrasound,
						evgroup_ultrasound_evbit_move);
			} else if (count > (uint16_t) ULTRASOUND_DIST_10CM_BITS) {
				rt_evbit_set_ISR(rt_evgroup_ultrasound,
						evgroup_ultrasound_evbit_move);
			} else if (count > (uint16_t) ULTRASOUND_DIST_5CM_BITS) {
				rt_evbit_set_ISR(rt_evgroup_ultrasound,
						evgroup_ultrasound_evbit_move);
			} else {
				rt_evbit_set_ISR(rt_evgroup_ultrasound,
						evgroup_ultrasound_evbit_move);
			}
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

/// auto-reload - triggering temperature measurement inside MCU
/// .xTimerPeriodInTicks = pdMS_TO_TICKS(6000) // 6 sec
void timer_trigger_temperature_measurement(TimerHandle_t xTimer) {
//	HAL_ADC_Start_DMA(&hadc, pData, Length)
//	trigger_temperature_measurement_by_DMA();
	HAL_ADC_Start_DMA(&hadc, (uint32_t*) temperature_measurement,
	SIZE_OF_TEMPERATURE_MEASURMENT_ARRAY);

//	ble_pDataSend[0] = 0x01;

//	ble_pDataSend[2] = 0x03;

//	if (temp++ == 1) {
//		ble_pDataSend[1] = 0x02;
//		ble_pDataSend[2] = 0xBC;
//		temp = 0;
//	} else {
//		ble_pDataSend[1] = 0x01;
//		ble_pDataSend[2] = 0xAA;
//	}
//	xQueueBleData toBeTransmit_ble_pData = { 0 };

//	toBeTransmit_ble_pData.info = ble_transmit;
//	toBeTransmit_ble_pData.command = 0x00;
//	toBeTransmit_ble_pData.valueReg1 = ble_pDataSend[1];
//	toBeTransmit_ble_pData.valueReg2 = ble_pDataSend[2];

//	rt_enqueue_ISR(rt_queue_ble, &toBeTransmit_ble_pData);

//	HAL_UART_Transmit_DMA(&huart3, (uint8_t*) ble_pDataSend, BLE_MAX_SIZE);
}

// temperature measurement completed? enqueue bluetooth :-)
/// sending raw data of temperature from MCU to BLE queue
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	xQueueBleData toBeTransmit_ble_pData = { 0 };
	toBeTransmit_ble_pData.info = ble_transmit;
	toBeTransmit_ble_pData.command = 0x00;
	toBeTransmit_ble_pData.valueReg1 = ((uint8_t*) &temperature_measurement)[2]; // MSB
	toBeTransmit_ble_pData.valueReg2 = ((uint8_t*) &temperature_measurement)[3]; // LSB
	rt_enqueue_ISR(rt_queue_ble, &toBeTransmit_ble_pData);
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

///	 start temperature measurement every period of this timer
	rt_timer_start(rt_timer_temperature_measurement, 100);

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

		// u2 to decimal
		uint16_t temp = ~((temp2 << 8) | temp1) + 1;
		temp /= 100;

		temp += 1;

		if (status & (1 << 0)) {
			QMC5883L_Read_Data(&X, &Y, &Z);

//			BLE_TRANSMIT_X
//			BLE_TRANSMIT_Y
//			BLE_TRANSMIT_Z

			xQueueBleData toBeTransmit_ble_pData = { 0 };
			toBeTransmit_ble_pData.info = ble_transmit;
			toBeTransmit_ble_pData.command = BLE_TRANSMIT_X;// 1111 1111 1010 1010

			type_casting.uint16[0] = int16_to_u2(X);

			toBeTransmit_ble_pData.valueReg1 = type_casting.uint8[1];//((uint8_t*) &X)[0]; // MSB // 1111 1111
			toBeTransmit_ble_pData.valueReg2 = type_casting.uint8[0];//((uint8_t*) &X)[1]; // LSB 1010 1010
			rt_enqueue_ISR(rt_queue_ble, &toBeTransmit_ble_pData);

			toBeTransmit_ble_pData.command = BLE_TRANSMIT_Y;
			type_casting.uint16[0] = int16_to_u2(Y);
			toBeTransmit_ble_pData.valueReg1 = type_casting.uint8[1];
			toBeTransmit_ble_pData.valueReg2 = type_casting.uint8[0];
			rt_enqueue_ISR(rt_queue_ble, &toBeTransmit_ble_pData);

//			type_casting.uint32 = 0x000000;
//			type_casting.uint8[0];

//			type_casting
//			type_casting.uint16[0] = X;

			//TODO: o tutaj skonczylem użyj unii, sprawdz debuggerem czy bd dzialac

			toBeTransmit_ble_pData.command = BLE_TRANSMIT_Z;
			type_casting.uint16[0] = int16_to_u2(Z);
			toBeTransmit_ble_pData.valueReg1 = type_casting.uint8[1];
			toBeTransmit_ble_pData.valueReg2 = type_casting.uint8[0];
			rt_enqueue_ISR(rt_queue_ble, &toBeTransmit_ble_pData);
		} else {
			X = 0;
			Y = 0;
			Z = 0;
		}

		taskYIELD();

//		if (NORMAL == QMC5883L_DataIsReady()) {
//		temperature = QMC5883L_Read_Temperature();
//		temperature /= 10;
//		}

	}

}
