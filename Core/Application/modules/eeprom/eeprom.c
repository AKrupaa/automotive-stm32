/*
 * eeprom.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#include "eeprom.h"
#include "i2c.h"

bool eeprom_init(void) {
	;
	return true;
}

//void start_condition(bool read_write) {
//	uint8_t addressing_memory_array = 0b10100000;
//	addressing_memory_array |= (read_write << 0);
//}

void eeprom_write(uint8_t where[2], uint8_t *pData, uint16_t size) {
	HAL_I2C_Master_Transmit(&hi2c1, EEPROM_MEMORY_ARRAY_ADDRESS, where, 2,
	HAL_MAX_DELAY);

	HAL_I2C_Master_Transmit(&hi2c1, EEPROM_MEMORY_ARRAY_ADDRESS, pData, size,
	HAL_MAX_DELAY);
}

void eeprom_read(uint8_t where[2], uint8_t *received_data, uint16_t size) {
	HAL_I2C_Master_Transmit(&hi2c1, EEPROM_MEMORY_ARRAY_ADDRESS, where, 2,
	HAL_MAX_DELAY);

	HAL_I2C_Master_Receive(&hi2c1, EEPROM_MEMORY_ARRAY_ADDRESS, received_data,
			size, HAL_MAX_DELAY);
}

