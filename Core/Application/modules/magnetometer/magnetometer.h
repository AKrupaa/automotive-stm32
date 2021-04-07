/*
 * magnetometer.h
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_MODULES_MAGNETOMETER_MAGNETOMETER_H_
#define APPLICATION_MODULES_MAGNETOMETER_MAGNETOMETER_H_
#include "stdbool.h"
#include "stdint.h"

bool magnetometer_init(void);

bool magnetometer_write(uint8_t reg_address, uint8_t *pData, uint16_t size);

bool magnetometer_read(uint8_t reg_address, uint8_t *buff, uint16_t size);

int magnetometer_get_X(void);

int magnetometer_get_Y(void);

int magnetometer_get_Z(void);

int magnetometer_get_temperature(void);

#endif /* APPLICATION_MODULES_MAGNETOMETER_MAGNETOMETER_H_ */
