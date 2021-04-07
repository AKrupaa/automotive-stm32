/*
 * h_bridge.h
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_MODULES_H_BRIDGE_H_BRIDGE_H_
#define APPLICATION_MODULES_H_BRIDGE_H_BRIDGE_H_

#include "stdbool.h"
#include "stdint.h"

bool h_bridge_init(void);

void h_bridge_set_left_duty(uint8_t percent);

void h_bridge_set_right_duty(uint8_t percent);

#endif /* APPLICATION_MODULES_H_BRIDGE_H_BRIDGE_H_ */
