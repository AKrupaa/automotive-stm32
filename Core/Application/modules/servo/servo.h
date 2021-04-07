/*
 * servo.h
 *
 *  Created on: Apr 7, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_MODULES_SERVO_SERVO_H_
#define APPLICATION_MODULES_SERVO_SERVO_H_
#include "stdbool.h"
#include "stdint.h"

bool servo_init(void);

void servo_set_duty(uint8_t percent);

#endif /* APPLICATION_MODULES_SERVO_SERVO_H_ */
