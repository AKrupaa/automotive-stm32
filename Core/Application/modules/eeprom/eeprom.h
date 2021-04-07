/*
 * eeprom.h
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_MODULES_EEPROM_EEPROM_H_
#define APPLICATION_MODULES_EEPROM_EEPROM_H_

#define EEPROM_MEMORY_ARRAY_ADDRESS 0b1010000

#include "stdbool.h"
#include "stdint.h"
#include "main.h"

bool eeprom_init(void);

//void start_condition(void);
void eeprom_write(uint8_t where[2], uint8_t *pData, uint16_t size);

void eeprom_read(uint8_t where[2], uint8_t *received_data, uint16_t size);

#endif /* APPLICATION_MODULES_EEPROM_EEPROM_H_ */
