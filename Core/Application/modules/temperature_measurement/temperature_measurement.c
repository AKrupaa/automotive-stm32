/*
 * temperature_measurement.c
 *
 *  Created on: Jul 5, 2021
 *      Author: Arkadiusz
 */

#include "temperature_measurement.h"
#include "adc.h"

uint32_t temperature_measurement[SIZE_OF_TEMPERATURE_MEASURMENT_ARRAY] = { 0 };

//void trigger_temperature_measurement_by_DMA(void) {
//	HAL_ADC_Start_DMA(&hadc, temperature_measurement, SIZE_OF_TEMPERATURE_MEASURMENT_ARRAY);
//}
