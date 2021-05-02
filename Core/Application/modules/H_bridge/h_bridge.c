/*
 * h_bridge.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */
#include "h_bridge.h"
#include "tim.h"

//#define CLOCK_CYCLES_PER_SECOND  72000000
//#define MAX_RELOAD               0xFFFF
//
//uint32_t period_cycles = CLOCK_CYCLES_PER_SECOND / freq;
//uint16_t prescaler = (uint16)(period_cycles / MAX_RELOAD + 1);
//uint16_t overflow = (uint16)((period_cycles + (prescaler / 2)) / prescaler);
//uint16_t duty = (uint16)(overflow / 2);

//INA Clockwise input
//INB Counter clockwise input
//#define RIGHT_PWM_HANDLER htim3
//#define RIGHT_PWM_CHANNEL
//#define SERVO_PWM_HANDLER htim2
//#define LEFT_PWM_HANDLER htim9
//htim3 RIGHT ENGINE
bool h_bridge_init(void) {
	;

//	htim2->Instance->CCR1
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

//	htim9.Instance->CCR2 = 0;
//	htim3.Instance->CCR3 = 0;
	return true;
}

void h_bridge_set_left_duty(uint8_t percent) {
	if (percent > 100)
		percent = 100;

	if (percent < 1)
		percent = 0;

	HAL_GPIO_WritePin(OUT_INa_ENGINE_LEFT_GPIO_Port, OUT_INa_ENGINE_LEFT_Pin,
			GPIO_PIN_SET);
	HAL_GPIO_WritePin(OUT_INnb_ENGINE_LEFT_GPIO_Port, OUT_INnb_ENGINE_LEFT_Pin,
			GPIO_PIN_RESET);

	HAL_GPIO_WritePin(OUT_INa_ENGINE_RIGHT_GPIO_Port,
			OUT_INa_ENGINE_RIGHT_GPIO_Port, GPIO_PIN_SET);
	HAL_GPIO_WritePin(OUT_INb_RIGHT_GPIO_Port, OUT_INb_RIGHT_Pin, GPIO_PIN_SET);
	uint32_t value = percent * htim9.Init.Period / 100;
	htim9.Instance->CCR2 = value;
}

void h_bridge_set_right_duty(uint8_t percent) {
	if (percent > 100)
		percent = 100;

	if (percent < 1)
		percent = 0;

	int value = percent * htim3.Init.Period / 100;
	htim3.Instance->CCR3 = value;
}

