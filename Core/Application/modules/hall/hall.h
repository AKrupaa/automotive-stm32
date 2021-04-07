/*
 * hall.h
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_MODULES_HALL_HALL_H_
#define APPLICATION_MODULES_HALL_HALL_H_
#include "main.h"

bool hall_init(void);

GPIO_PinState hall_left_read_status(void);
GPIO_PinState hall_right_read_status(void);
//GPIO_PinState hall_front_read_status(void);
//GPIO_PinState hall_back_read_status(void);

#endif /* APPLICATION_MODULES_HALL_HALL_H_ */
