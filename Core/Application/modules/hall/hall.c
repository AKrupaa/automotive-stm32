/*
 * hall.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#include "hall.h"

typedef enum {
	hall_detected = 0,
	hall_not_detected
} hall_detection_t;

/**
 *
 * @return true
 */
bool hall_init(void) {
	;
	return true;
}

GPIO_PinState hall_left_read_status(void) {
	return HAL_GPIO_ReadPin(INPUT_HALL_LEFT_GPIO_Port, INPUT_HALL_LEFT_Pin);
}

GPIO_PinState hall_right_read_status(void) {
	return HAL_GPIO_ReadPin(INPUT_HALL_RIGHT_GPIO_Port, INPUT_HALL_RIGHT_Pin);
}
//GPIO_PinState hall_front_read_status(void) {
//	return HAL_GPIO_ReadPin(INPUT_, INPUT_HALL_LEFT_Pin);
//}
//GPIO_PinState hall_back_read_status(void) {
//	return HAL_GPIO_ReadPin(INPUT_HALL_LEFT_GPIO_Port, INPUT_HALL_LEFT_Pin);
//}
