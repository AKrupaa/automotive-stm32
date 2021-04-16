/*
 * bluetooth_le.h
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_MODULES_BLUETOOTH_LOW_ENERGY_BLUETOOTH_LE_H_
#define APPLICATION_MODULES_BLUETOOTH_LOW_ENERGY_BLUETOOTH_LE_H_
//#include "stdbool.h"
#include "main.h"
#include "usart.h"
#include "string.h"
#include "runtime.h"
//#include <stdlib.h>
//#include <stdio.h>

#define ble_turn_on_transmittion HAL_GPIO_WritePin(OUT_BLE_EN_GPIO_Port, OUT_BLE_EN_Pin, GPIO_PIN_RESET)
#define ble_turn_off_transmittion HAL_GPIO_WritePin(OUT_BLE_EN_GPIO_Port, OUT_BLE_EN_Pin, GPIO_PIN_SET)

typedef enum {

	evgroup_ble_evbit_received = 0,
	evgroup_ble_evbit_N,

} ble_evgroup_bits_t;

typedef enum {
	transmit_power_plus_4_dBm = 0,
	transmit_power_plus_0_dBm,
	transmit_power_minus_4_dBm,
	transmit_power_minus_8_dBm,
	transmit_power_minus_12_dBm,
	transmit_power_minus_16_dBm,
	transmit_power_minus_20_dBm,
	transmit_power_minus_30_dBm,
	transmit_power_minus_40_dBm,
} ble_transmit_power_t;

typedef struct {
	char info[10];
	uint32_t value;
} xQueueBleData;

void ble_send_queue(xQueueBleData *data, ble_evgroup_bits_t evbit);

bool ble_init(void);

bool ble_test_command(void);

int ble_get_MAC_Address(void);

bool ble_set_MAC(int value);

bool ble_set_BOUD(int value);

int ble_get_BOUD(void);
// char * name = (char*) malloc(sizeof(char) * 10);
// char[0] = 'x';
// char[1] = 'd';
// char[2] = '\0';
// strcpy(name, 'xd');
// free(name);
bool ble_set_device_name(char *name);

bool ble_get_device_name(char *buff);

bool ble_set_transmit_power(ble_transmit_power_t power);

bool ble_reset_module(void);

bool ble_restore_default_values(void);

bool ble_broadcast_data(uint8_t *data, int size);

//bool ble_set_customized_MAC_address_

bool ble_set_broadcast_interval(int interval_in_ms);

bool ble_reset_interval(void);

bool ble_low_power_sleep_mode(void);

#endif /* APPLICATION_MODULES_BLUETOOTH_LOW_ENERGY_BLUETOOTH_LE_H_ */
