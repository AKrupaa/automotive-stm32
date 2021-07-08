/*
 * eyes.c
 *
 *  Created on: Mar 29, 2021
 *      Author: Arkadiusz
 */

//#include "task_eyes.h"
#include "FreeRTOS.h"
#include "task.h"
#include "runtime.h"
#include "gpio.h"
#include "tim.h"

/* ************************************************************************** */
// callback
/* ************************************************************************** */
void timer_ultrasound_sensor_tigger(TimerHandle_t xTimer) {

	// set gpio ultrasound trigger
	HAL_GPIO_WritePin(OUT_ULTRASOUND_TRIG_GPIO_Port, OUT_ULTRASOUND_TRIG_Pin, GPIO_PIN_SET);

	// set timer to 10 us, and start!
	HAL_TIM_Base_Start_IT(&htim10);

	// after ... in another interrupt (htim10) clear gpio ultrasound trigger
	//	void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)

	// also... in async is waiting for rising / falling edge (void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin))
	// if rising edge start timer 4 for counting up
	// if falling edge stop timer 4
	// calulcate difference
	// calulcate distance between obstacle and vehicle
}

void task_eyes(void *pvParameters) {

	// start auto-reloaded timer for triggering ultrasound sensor
	rt_timer_start(rt_timer_ultrasound_sensor_trigger, 100);

	(void*) pvParameters;

	for (;;) {

		taskYIELD();
	}

}
