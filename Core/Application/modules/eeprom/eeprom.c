/*
 * eeprom.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#include "eeprom.h"
#include "i2c.h"

bool eeprom_init(void) {

	if (HAL_I2C_IsDeviceReady(&hi2c1, EEPROM_I2C_ADDRESS, EEPROM_MAX_TRIALS,
	HAL_MAX_DELAY) != HAL_OK) {
		return false;
	}
	return true;

}

bool eeprom_read(uint8_t *pBuffer, uint16_t ReadAddr, uint16_t *NumByteToRead) {

	uint32_t buffersize = *NumByteToRead;

	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Read(&hi2c1, EEPROM_I2C_ADDRESS, (uint16_t) ReadAddr,
	I2C_MEMADD_SIZE_16BIT, pBuffer, buffersize, EEPROM_I2C_TIMEOUT);

	if (status != HAL_OK) {
		return false;
	}

	return true;
}

bool eeprom_write(uint8_t *pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite) {

}

bool eeprom_write_page(uint8_t *pBuffer, uint16_t WriteAddr,
		uint8_t *NumByteToWrite) {
	uint32_t buffersize = *NumByteToWrite;

	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Write(&hi2c1, EEPROM_I2C_ADDRESS, (uint16_t) WriteAddr,
	I2C_MEMADD_SIZE_16BIT, pBuffer, buffersize, EEPROM_I2C_TIMEOUT);
	if (status != HAL_OK) {
		return false;
	}

	return true;
}
