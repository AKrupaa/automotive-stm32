/*
 * eeprom.h
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_MODULES_EEPROM_EEPROM_H_
#define APPLICATION_MODULES_EEPROM_EEPROM_H_

#define EEPROM_MEMORY_ARRAY_ADDRESS 0x3C
//#define EEPROM_MEMORY_ARRAY_ADDRESS 0x3D nwm, duzo tych adresow

#include "stdbool.h"
#include "stdint.h"
#include "main.h"

//#define EEPROM_I2C_ADDRESS                    (0b1010000 << 1)
#define EEPROM_I2C_ADDRESS          0xA0
#define EEPROM_MAX_TRIALS           3000
#define EEPROM_I2C_TIMEOUT          100

//The Page Write mode allows up to 32 byte to be written in a single Write cycle
#define EEPROM_PAGESIZE             32
#define EEPROM_MAX_SIZE             0x2000 /* 64Kbit*/

//#define EEPROM_OK                   0
//#define EEPROM_FAIL                 1
//#define EEPROM_TIMEOUT              2

bool eeprom_init(void);

bool eeprom_write(uint8_t *pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);

bool eeprom_read(uint8_t *pBuffer, uint16_t ReadAddr, uint16_t *NumByteToRead);

bool eeprom_write_page(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite);

#endif /* APPLICATION_MODULES_EEPROM_EEPROM_H_ */
