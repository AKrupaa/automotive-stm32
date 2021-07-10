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

volatile uint16_t ULTRASOUND_PROPER_DISTANCE_u16 = (uint16_t) ULTRASOUND_DIST_40CM_BITS;

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

uint16_t ultrasound_select_proper_distance(uint8_t code) {
	if (code == dist5) {
		return (uint16_t) ULTRASOUND_DIST_5CM_BITS;
	} else if (code == dist10) {
		return (uint16_t) ULTRASOUND_DIST_10CM_BITS;
	} else if (code == dist15) {
		return (uint16_t) ULTRASOUND_DIST_15CM_BITS;
	} else if (code == dist20) {
		return (uint16_t) ULTRASOUND_DIST_20CM_BITS;
	} else if (code == dist25) {
		return (uint16_t) ULTRASOUND_DIST_25CM_BITS;
	} else if (code == dist30) {
		return (uint16_t) ULTRASOUND_DIST_30CM_BITS;
	} else if (code == dist35) {
		return (uint16_t) ULTRASOUND_DIST_35CM_BITS;
	} else if (code == dist40) {
		return (uint16_t) ULTRASOUND_DIST_40CM_BITS;
	} else if (code == dist50) {
		return (uint16_t) ULTRASOUND_DIST_50CM_BITS;
	} else if (code == dist60) {
		return (uint16_t) ULTRASOUND_DIST_60CM_BITS;
	} else if (code == dist70) {
		return (uint16_t) ULTRASOUND_DIST_70CM_BITS;
	} else if (code == dist80) {
		return (uint16_t) ULTRASOUND_DIST_80CM_BITS;
	} else {
		return (uint16_t) ULTRASOUND_DIST_80CM_BITS;
	}
}

