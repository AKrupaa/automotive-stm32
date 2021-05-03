/*
 * servo.c
 *
 *  Created on: Apr 7, 2021
 *      Author: Arkadiusz
 */
#include "servo.h"
#include "tim.h"

bool servo_init(void) {
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
//	htim2.Instance->CCR1 = 0;
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
	return true;
}

void servo_set_duty(uint8_t percent) {
	if (percent > 100)
		percent = 100;

	if (percent < 1)
		percent = 0;

	uint32_t value = percent * htim2.Init.Period / 100;
//	htim9.Instance->CCR2 = value;
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, value);
}
