/*
 * magnetometer.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */
#include "magnetometer.h"
#include "i2c.h"

#define MAGNETOMETR_DEVICE_ADDRESS 0b0001101
#define MAGNETOMETR_X_LSB_Register 0x00
#define MAGNETOMETR_X_MSB_Register 0x01
#define MAGNETOMETR_Y_LSB_Register 0x02
#define MAGNETOMETR_Y_MSB_Register 0x03
#define MAGNETOMETR_Z_LSB_Register 0x04
#define MAGNETOMETR_Z_MSB_Register 0x05
#define MAGNETOMETR_STATUS_Register 0x06
#define MAGNETOMETR_TEMPERATURE_LSB_REGISTER 0x07
#define MAGNETOMETR_TEMPERATURE_MSB_REGISTER 0x08
#define MAGNETOMETR_CONTROL1_REGISTER 0x09
#define MAGNETOMETR_CONTROL2_REGISTER 0x0A
#define MAGNETOMETR_PERIOD_REGISTER 0x0B
#define MAGNETOMETR_CHIP_ID_REGISTER 0x0D

bool magnetometer_init(void) {
	uint8_t buff = 0;

	magnetometer_read(MAGNETOMETR_CHIP_ID_REGISTER, &buff, 1);
	if (buff != 0xFF)
		return false;

	// soft restart
	magnetometer_read(MAGNETOMETR_CONTROL2_REGISTER, &buff, 1);
	buff |= (0b1 << 7); // soft restart
	magnetometer_write(MAGNETOMETR_CONTROL2_REGISTER, &buff, 1);

	magnetometer_read(MAGNETOMETR_CONTROL1_REGISTER, &buff, 1);
	buff |= (0b10 << 0); // Continuous mode
	magnetometer_write(MAGNETOMETR_CONTROL1_REGISTER, &buff, 1);

	magnetometer_read(MAGNETOMETR_CONTROL2_REGISTER, &buff, 1);
	buff |= (0b1 << 0); // disable interrupt PIN
	buff |= (0b1 << 6); // Enable pointer roll-over function
	magnetometer_write(MAGNETOMETR_CONTROL2_REGISTER, &buff, 1);
	return true;
}

bool magnetometer_write(uint8_t reg_address, uint8_t *pData, uint16_t size) {
	HAL_I2C_Master_Transmit(&hi2c1, MAGNETOMETR_DEVICE_ADDRESS, pData, size,
	HAL_MAX_DELAY);
	return true;
}
bool magnetometer_read(uint8_t reg_address, uint8_t *buff, uint16_t size) {
	HAL_I2C_Master_Receive(&hi2c1, MAGNETOMETR_DEVICE_ADDRESS, buff, size,
	HAL_MAX_DELAY);
	return true;
}

int magnetometer_get_X(void) {
	uint8_t buff[2];
	magnetometer_read(MAGNETOMETR_X_LSB_Register, buff, sizeof(buff));
	return (int) ((buff[1] << 8) | buff[0]);
}

int magnetometer_get_Y(void) {
	uint8_t buff[2];
	magnetometer_read(MAGNETOMETR_Y_LSB_Register, buff, sizeof(buff));
	return (int) ((buff[1] << 8) | buff[0]);
}

int magnetometer_get_Z(void) {
	uint8_t buff[2];
	magnetometer_read(MAGNETOMETR_Z_LSB_Register, buff, sizeof(buff));
	return (int) ((buff[1] << 8) | buff[0]);
}

int magnetometer_get_temperature(void) {
	uint8_t buff[2];
	magnetometer_read(MAGNETOMETR_TEMPERATURE_LSB_REGISTER, buff, sizeof(buff));

	uint16_t buf = ((buff[1] << 8) | buff[0]);	// U2
	buf = ~buf + 1; // decimal
	return (int) buf / 100; // our value
}
