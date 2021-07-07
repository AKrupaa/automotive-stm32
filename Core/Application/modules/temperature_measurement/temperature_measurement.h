/*
 * temperature_measurement.h
 *
 *  Created on: Jul 5, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_MODULES_TEMPERATURE_MEASUREMENT_TEMPERATURE_MEASUREMENT_H_
#define APPLICATION_MODULES_TEMPERATURE_MEASUREMENT_TEMPERATURE_MEASUREMENT_H_

#define SIZE_OF_TEMPERATURE_MEASURMENT_ARRAY 1
#include "FreeRTOS.h"
#include "timers.h"

//void trigger_temperature_measurement_by_DMA(void);
void timer_trigger_temperature_measurement(TimerHandle_t xTimer);

#endif /* APPLICATION_MODULES_TEMPERATURE_MEASUREMENT_TEMPERATURE_MEASUREMENT_H_ */
