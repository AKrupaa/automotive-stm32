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
#include "optocoupler.h"
#include "ultrasound.h"
#include "temperature_measurement.h"
#include "bluetooth_le.h"
#include "stdbool.h"
#include "runtime.h"
#include "adc.h"
#include "tim.h"
#include "utility.h"
#include <math.h>
#include "adc.h"

extern volatile uint16_t ULTRASOUND_PROPER_DISTANCE_u16;

union {
	uint32_t uint32;
	uint16_t uint16[2];
	uint8_t uint8[4];
} type_casting;

//static uint32_t ultrasound_time = 0U;
bool ultrasound_was = false;
//bool ultrasound_done = false;
uint8_t pData[BLE_MAX_SIZE];
volatile uint16_t counter = 0;
extern char temperature_measurement[SIZE_OF_TEMPERATURE_MEASURMENT_ARRAY];
// interrupt pin callback
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//	IRQ_ULTRASOUND_ECHO_Pin
	if (GPIO_Pin & IRQ_ULTRASOUND_ECHO_Pin) {

		if (HAL_GPIO_ReadPin(IRQ_ULTRASOUND_ECHO_GPIO_Port,
		IRQ_ULTRASOUND_ECHO_Pin)) {
			TIM4->CNT = 0;
			HAL_TIM_Base_Start(&htim4);
		} else {
			HAL_TIM_Base_Stop(&htim4);
			uint16_t count = TIM4->CNT;

			/// 	clear 	(if > 30 cm) 	==> 	allowed to drive forward
			/// 	set 	(if < 30 cm) 	==> 	forbidden to drive forward

//			uint16_t dis30 = (uint16_t) ULTRASOUND_PROPER_DISTANCE;
			if (count > ULTRASOUND_PROPER_DISTANCE_u16) {
				rt_evbit_set_ISR(rt_evgroup_ultrasound,
						evgroup_ultrasound_evbit_move);
			} else {
				rt_evbit_clear_ISR(rt_evgroup_ultrasound,
						evgroup_ultrasound_evbit_move);
			}

			if (counter > 8) {
				counter = 0;
				xQueueBleData toBeTransmit_ble_pData = { 0 };
				toBeTransmit_ble_pData.info = ble_transmit;
				toBeTransmit_ble_pData.command =
						(uint8_t) BLE_TRANSMIT_ULTRASOUND_VALUE;
				toBeTransmit_ble_pData.valueReg1 = ((uint8_t*) &count)[0]; // LSB
				toBeTransmit_ble_pData.valueReg2 = ((uint8_t*) &count)[1]; // MSB
				rt_enqueue_ISR(rt_queue_ble, &toBeTransmit_ble_pData);
			}

			counter++;

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
//	HAL_ADC_Start_DMA(&hadc, (uint32_t*) temperature_measurement,
//	SIZE_OF_TEMPERATURE_MEASURMENT_ARRAY);
}

uint32_t fun(uint32_t ac) {
	ac += 1;
	return ac;
}

typedef enum {
	adc_phototransitor_front = 0, adc_phototransistor_back, adc_N,
} selectADC_t;

volatile selectADC_t selectADC = adc_phototransitor_front;
// temperature measurement completed? enqueue bluetooth :-)
/// sending raw data of temperature from MCU to BLE queue
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
//	xQueueBleData toBeTransmit_ble_pData = { 0 };
//	toBeTransmit_ble_pData.info = ble_transmit;
//	toBeTransmit_ble_pData.command = 0x00;
//	toBeTransmit_ble_pData.valueReg1 = ((uint8_t*) &temperature_measurement)[2]; // MSB
//	toBeTransmit_ble_pData.valueReg2 = ((uint8_t*) &temperature_measurement)[3]; // LSB
//	rt_enqueue_ISR(rt_queue_ble, &toBeTransmit_ble_pData);
	uint8_t raw_value = (uint8_t) HAL_ADC_GetValue(hadc);
	xQueueBleData toBeTransmit_ble_pData = { 0 };
	toBeTransmit_ble_pData.info = ble_transmit;
	toBeTransmit_ble_pData.valueReg1 = raw_value;
	toBeTransmit_ble_pData.valueReg2 = 0x00;

	switch (selectADC) {
	case adc_phototransitor_front:
		toBeTransmit_ble_pData.command =
		BLE_TRANSMIT_PHOTOTRANSISTOR_FRONT_VALUE;
		break;
	case adc_phototransistor_back:
		toBeTransmit_ble_pData.command =
		BLE_TRANSMIT_PHOTOTRANSISTOR_BACK_VALUE;
		break;
	default:
		return;
	}

	rt_enqueue_ISR(rt_queue_ble, &toBeTransmit_ble_pData);
}

void task_sensors(void *pvParameters) {
	(void*) pvParameters;

	QMC5883L_Initialize(MODE_CONTROL_CONTINUOUS, OUTPUT_DATA_RATE_200HZ,
			FULL_SCALE_2G, OVER_SAMPLE_RATIO_128);
	QMC5883L_InterruptConfig(INTERRUPT_DISABLE);

//Mode Register
//Continuous-Measurement Mode
	QMC5883L_Write_Reg(0x02, 0x00);
//	uint8_t whereADC = 0;

	for (;;) {

		int16_t X = 0;
		int16_t Y = 0;
		int16_t Z = 0;

		static uint32_t PreviousTicksMagnetometer = 0U;
		static uint32_t PreviousTicksADC = 0U;
		uint32_t CurrentTicks = (uint32_t) xTaskGetTickCount();
		if ((CurrentTicks - PreviousTicksMagnetometer) >= 500u) { // 5 ms
			PreviousTicksMagnetometer = (uint32_t) xTaskGetTickCount();
			QMC5883L_Read_Data(&X, &Y, &Z);
//			BLE_TRANSMIT_X
//			BLE_TRANSMIT_Y
//			BLE_TRANSMIT_Z

			QMC5883L_Scale(&X, &Y, &Z);

			xQueueBleData toBeTransmit_ble_pData = { 0 };
			toBeTransmit_ble_pData.info = ble_transmit;
			toBeTransmit_ble_pData.command = BLE_TRANSMIT_X;

			type_casting.uint16[0] = X; //int16_to_u2(X);
			toBeTransmit_ble_pData.valueReg1 = type_casting.uint8[0]; //((uint8_t*) &X)[0]; // MSB // 1111 1111
			toBeTransmit_ble_pData.valueReg2 = type_casting.uint8[1]; //((uint8_t*) &X)[1]; // LSB 1010 1010
			rt_enqueue(rt_queue_ble, &toBeTransmit_ble_pData);

			toBeTransmit_ble_pData.command = BLE_TRANSMIT_Y;
			type_casting.uint16[0] = Y; //int16_to_u2(Y);
			toBeTransmit_ble_pData.valueReg1 = type_casting.uint8[0];
			toBeTransmit_ble_pData.valueReg2 = type_casting.uint8[1];
			rt_enqueue(rt_queue_ble, &toBeTransmit_ble_pData);

			toBeTransmit_ble_pData.command = BLE_TRANSMIT_Z;
			type_casting.uint16[0] = Z; //int16_to_u2(Z);
			toBeTransmit_ble_pData.valueReg1 = type_casting.uint8[0];
			toBeTransmit_ble_pData.valueReg2 = type_casting.uint8[1];
			rt_enqueue(rt_queue_ble, &toBeTransmit_ble_pData);

		}

		if ((CurrentTicks - PreviousTicksADC) >= 200u) { // 200 ms
			PreviousTicksADC = (uint32_t) xTaskGetTickCount();

			if (selectADC == adc_phototransitor_front) {
				ADC_ChannelConfTypeDef sConfig = { 0 };
				/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
				 */
				sConfig.Channel = ADC_CHANNEL_1; // photo back1
				//	sConfig.Channel = ADC_CHANNEL_7; // photo front
				sConfig.Rank = ADC_REGULAR_RANK_1;
				sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES;
				if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
					Error_Handler();
				}
				HAL_ADC_ConfigChannel(&hadc, &sConfig);
			}

			if (selectADC == adc_phototransistor_back) {
				ADC_ChannelConfTypeDef sConfig = { 0 };
				/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
				 */
//					sConfig.Channel = ADC_CHANNEL_1; // photo back1
				sConfig.Channel = ADC_CHANNEL_7; // photo front
				sConfig.Rank = ADC_REGULAR_RANK_1;
				sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES;
				if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
					Error_Handler();
				}
				HAL_ADC_ConfigChannel(&hadc, &sConfig);
			}

			HAL_ADC_Start_IT(&hadc);
			selectADC++;
			if (selectADC == adc_N) {
				selectADC = 0;
			}
		}
		taskYIELD();
	}

}
