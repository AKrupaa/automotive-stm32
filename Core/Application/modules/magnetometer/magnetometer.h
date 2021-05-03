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

#define MAGNETOMETR_DEVICE_ADDRESS (0x0D<<1)
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

//https://github.com/Farondis/QMC5883L-stm32-hal

#define QMC5883L_ADDRESS  		(0x0D<<1)
#define QMC5883L_I2C_PORT		&hi2c1

#define QMC5883L_DATA_READ_X_LSB	0x00
#define QMC5883L_DATA_READ_X_MSB	0x01
#define QMC5883L_DATA_READ_Y_LSB	0x02
#define QMC5883L_DATA_READ_Y_MSB	0x03
#define QMC5883L_DATA_READ_Z_LSB	0x04
#define QMC5883L_DATA_READ_Z_MSB	0x05
#define QMC5883L_TEMP_READ_LSB		0x07
#define QMC5883L_TEMP_READ_MSB		0x08
#define QMC5883L_STATUS		        0x06 // DOR | OVL | DRDY
#define QMC5883L_CONFIG_1			0x09 // OSR | RNG | ODR | MODE
#define QMC5883L_CONFIG_2			0x0A // SOFT_RST | ROL_PNT | INT_ENB
#define QMC5883L_CONFIG_3			0x0B // SET/RESET Period FBR [7:0]
#define QMC5883L_ID					0x0D

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288f
#endif

#define QMC5883L_SCALE_FACTOR 		0.732421875f
#define QMC5883L_CONVERT_GAUSS_2G 	12000.0f
#define QMC5883L_CONVERT_GAUSS_8G 	3000.0f
#define QMC5883L_CONVERT_MICROTESLA 	100
#define QMC5883L_DECLINATION_ANGLE	93.67/1000  // radian, Tekirdag/Turkey

/**
 *
 * @return true if correctly
 */
bool magnetometer_init(void);

/**
 *
 * @param reg_address
 * @param pData
 * @param size
 * @return
 */
bool magnetometer_write(uint8_t reg_address, uint8_t *pData, uint16_t size);

/**
 *
 * @param reg_address
 * @param buff
 * @param size
 * @return
 */
bool magnetometer_read(uint8_t reg_address, uint8_t *buff, uint16_t size);

/**
 *
 * @return X value
 */
int magnetometer_get_X(void);

/**
 *
 * @return Y value
 */
int magnetometer_get_Y(void);

/**
 *
 * @return Z value
 */
int magnetometer_get_Z(void);

/**
 *
 * @return temerature
 */
int magnetometer_get_temperature(void);

typedef enum STATUS_VARIABLES {
	NORMAL,
	NO_NEW_DATA,
	NEW_DATA_IS_READY,
	DATA_OVERFLOW,
	DATA_SKIPPED_FOR_READING
} _qmc5883l_status;

typedef enum MODE_VARIABLES {
	MODE_CONTROL_STANDBY = 0x00, MODE_CONTROL_CONTINUOUS = 0x01
} _qmc5883l_MODE;

typedef enum ODR_VARIABLES {
	OUTPUT_DATA_RATE_10HZ = 0x00,
	OUTPUT_DATA_RATE_50HZ = 0x04,
	OUTPUT_DATA_RATE_100HZ = 0x08,
	OUTPUT_DATA_RATE_200HZ = 0x0C
} _qmc5883l_ODR;

typedef enum RNG_VARIABLES {
	FULL_SCALE_2G = 0x00, FULL_SCALE_8G = 0x10
} _qmc5883l_RNG;

typedef enum OSR_VARIABLES {
	OVER_SAMPLE_RATIO_512 = 0x00,
	OVER_SAMPLE_RATIO_256 = 0x40,
	OVER_SAMPLE_RATIO_128 = 0x80,
	OVER_SAMPLE_RATIO_64 = 0xC0
} _qmc5883l_OSR;

typedef enum INTTERRUPT_VARIABLES {
	INTERRUPT_DISABLE, INTERRUPT_ENABLE
} _qmc5883l_INT;

static float Xmin, Xmax, Ymin, Ymax;
static int16_t X, Y, Z;

uint8_t QMC5883L_Read_Reg(uint8_t reg);
void QMC5883L_Write_Reg(uint8_t reg, uint8_t data);
_qmc5883l_status QMC5883L_DataIsReady(void);
_qmc5883l_status QMC5883L_DataIsOverflow(void);
_qmc5883l_status QMC5883L_DataIsSkipped(void);
int16_t QMC5883L_Read_Temperature(void);
void QMC5883L_Read_Data(int16_t *MagX, int16_t *MagY, int16_t *MagZ);
void QMC5883L_Initialize(_qmc5883l_MODE MODE, _qmc5883l_ODR ODR,
		_qmc5883l_RNG RNG, _qmc5883l_OSR OSR);
void QMC5883L_Reset(void);
void QMC5883L_InterruptConfig(_qmc5883l_INT INT);
void QMC5883L_ResetCalibration(void);
float QMC5883L_Heading(int16_t Xraw, int16_t Yraw, int16_t Zraw);
void QMC5883L_Scale(int16_t *X, int16_t *Y, int16_t *Z);

#endif /* APPLICATION_MODULES_MAGNETOMETER_MAGNETOMETER_H_ */
