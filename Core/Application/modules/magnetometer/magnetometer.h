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

#define MAGNETOMETR_DEVICE_ADDRESS 0b0001101

bool magnetometer_init(void);
bool magnetometer_write(uint8_t reg_address, uint8_t *pData, uint16_t size);
bool magnetometer_read(uint8_t reg_address, uint8_t *pData, uint16_t size);

#endif /* APPLICATION_MODULES_MAGNETOMETER_MAGNETOMETER_H_ */
