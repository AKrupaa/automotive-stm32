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

/**
 *
 * @return true if initialized
 */
bool h_bridge_init(void);

/**
 *
 * @param percent PWM percentage fill
 */
void h_bridge_set_left_duty(int percent);

/**
 *
 * @param percent PWM percentage fill
 */
void h_bridge_set_right_duty(int percent);

void h_bridge_cw_left(void);

void h_bridge_cw_right(void);

void h_bridge_ccw_left(void);

void h_bridge_ccw_right(void);

/**
 * Coast mode allows the motor to “coast” or “idle” when power is no longer applied.
 * This means running the motor then cutting power output to it will not stop “on a dime”, but will instead continue to spin by inertia.
 */
void h_bridge_coast(void);

void h_bridge_stop(void);

#endif /* APPLICATION_MODULES_H_BRIDGE_H_BRIDGE_H_ */
