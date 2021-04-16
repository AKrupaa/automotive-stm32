/*
 * proximity.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#include <ultrasound_sensor/ultrasound.h>

#define MAX_SENSOR_DISTANCE 500 // Maximum sensor distance can be as high as 500cm, no reason to wait for ping longer than sound takes to travel this distance and back. Default=500
#define US_ROUNDTRIP_CM 57      // Microseconds (uS) it takes sound to travel round-trip 1cm (2cm total), uses integer to save compiled code space. Default=57
#define US_ROUNDTRIP_IN 146     // Microseconds (uS) it takes sound to travel round-trip 1 inch (2 inches total), uses integer to save compiled code space. Defalult=146

bool ultrasound_init(void) {
	;
	return true;
}

void ultrasound_trig(void) {
	HAL_GPIO_WritePin(OUT_ULTRASOUND_TRIG_GPIO_Port, OUT_ULTRASOUND_TRIG_Pin,
			GPIO_PIN_SET);
//	HAL_Delay(0.01);
	HAL_GPIO_WritePin(OUT_ULTRASOUND_TRIG_GPIO_Port, OUT_ULTRASOUND_TRIG_Pin,
			GPIO_PIN_RESET);
}
