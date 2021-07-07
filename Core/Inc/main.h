/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdio.h>
#include "stdbool.h"
#include "stdint.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADC_BATTERY_VOLTAGE_Pin GPIO_PIN_0
#define ADC_BATTERY_VOLTAGE_GPIO_Port GPIOC
#define OUT_INa_ENGINE_LEFT_Pin GPIO_PIN_1
#define OUT_INa_ENGINE_LEFT_GPIO_Port GPIOC
#define OUT_INb_ENGINE_LEFT_Pin GPIO_PIN_2
#define OUT_INb_ENGINE_LEFT_GPIO_Port GPIOC
#define OUT_SEL0_ENGINE_LEFT_Pin GPIO_PIN_3
#define OUT_SEL0_ENGINE_LEFT_GPIO_Port GPIOC
#define PWM_ENGINE_LEFT_Pin GPIO_PIN_0
#define PWM_ENGINE_LEFT_GPIO_Port GPIOA
#define ADC_PHOTO_BACK_Pin GPIO_PIN_1
#define ADC_PHOTO_BACK_GPIO_Port GPIOA
#define ADC_OPTO_LEFT_Pin GPIO_PIN_2
#define ADC_OPTO_LEFT_GPIO_Port GPIOA
#define OUT_OPTO_EN_LEFT_Pin GPIO_PIN_3
#define OUT_OPTO_EN_LEFT_GPIO_Port GPIOA
#define ADC_PHOTO_FRONT_Pin GPIO_PIN_7
#define ADC_PHOTO_FRONT_GPIO_Port GPIOA
#define OUT_BLE_EN_Pin GPIO_PIN_4
#define OUT_BLE_EN_GPIO_Port GPIOC
#define OUT_BLE_TEST_Pin GPIO_PIN_5
#define OUT_BLE_TEST_GPIO_Port GPIOC
#define IRQ_BLE_Pin GPIO_PIN_0
#define IRQ_BLE_GPIO_Port GPIOB
#define IRQ_BLE_EXTI_IRQn EXTI0_IRQn
#define IRQ_ULTRASOUND_ECHO_Pin GPIO_PIN_1
#define IRQ_ULTRASOUND_ECHO_GPIO_Port GPIOB
#define INPUT_HALL_LEFT_Pin GPIO_PIN_12
#define INPUT_HALL_LEFT_GPIO_Port GPIOB
#define PWM_SERVO_Pin GPIO_PIN_14
#define PWM_SERVO_GPIO_Port GPIOB
#define ADC_OPTO_RIGHT_Pin GPIO_PIN_15
#define ADC_OPTO_RIGHT_GPIO_Port GPIOB
#define OUT_ULTRASOUND_TRIG_Pin GPIO_PIN_6
#define OUT_ULTRASOUND_TRIG_GPIO_Port GPIOC
#define IN_HALL_FRONT_Pin GPIO_PIN_7
#define IN_HALL_FRONT_GPIO_Port GPIOC
#define PWM_ENGINE_RIGHT_Pin GPIO_PIN_8
#define PWM_ENGINE_RIGHT_GPIO_Port GPIOC
#define OUT_INb_ENGINE_RIGHT_Pin GPIO_PIN_9
#define OUT_INb_ENGINE_RIGHT_GPIO_Port GPIOC
#define OUT_INa_ENGINE_RIGHT_Pin GPIO_PIN_8
#define OUT_INa_ENGINE_RIGHT_GPIO_Port GPIOA
#define OUT_SEL0_ENGINE_RIGHT_Pin GPIO_PIN_9
#define OUT_SEL0_ENGINE_RIGHT_GPIO_Port GPIOA
#define OUT_OPTO_EN_RIGHT_Pin GPIO_PIN_10
#define OUT_OPTO_EN_RIGHT_GPIO_Port GPIOA
#define INPUT_HALL_RIGHT_Pin GPIO_PIN_11
#define INPUT_HALL_RIGHT_GPIO_Port GPIOA
#define OUT_LED0_Pin GPIO_PIN_15
#define OUT_LED0_GPIO_Port GPIOA
#define OUT_LED1_Pin GPIO_PIN_10
#define OUT_LED1_GPIO_Port GPIOC
#define OUT_LED2_Pin GPIO_PIN_11
#define OUT_LED2_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
