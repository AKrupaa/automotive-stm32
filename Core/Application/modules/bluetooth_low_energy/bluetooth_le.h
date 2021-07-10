/*
 * bluetooth_le.h
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_MODULES_BLUETOOTH_LOW_ENERGY_BLUETOOTH_LE_H_
#define APPLICATION_MODULES_BLUETOOTH_LOW_ENERGY_BLUETOOTH_LE_H_
#include "main.h"
#include "usart.h"
#include "string.h"
#include "runtime.h"

#define ble_turn_on_transmittion HAL_GPIO_WritePin(OUT_BLE_EN_GPIO_Port, OUT_BLE_EN_Pin, GPIO_PIN_RESET)
#define ble_turn_off_transmittion HAL_GPIO_WritePin(OUT_BLE_EN_GPIO_Port, OUT_BLE_EN_Pin, GPIO_PIN_SET)

#define BLE_MAX_SIZE  3

#define BLE_TERMINATOR "\r"
#define BLE_OK "OK\r"
#define BLE_TEST_COMMAND "AT\r"
#define BLE_MODULE_VERSION_COMMAND "AT+VERSION\r"
#define BLE_RESTORE_DEFAULT_COMMAND "AT+DEFAULT\r"
#define BLE_RESET_COMMAND "AT+RESET\r"
#define BLE_RESET_CONNECTION_COMMAND "AT+CIT=" 			// AT + CIT = 300 \ r [20ms-2000ms]
#define BLE_LOW_POWER_MODE_COMMAND "AT+SLEEP\r"

#define BLE_GET_MAC_COMMAND "AT+ADDR\r"
#define BLE_GET_BOUD_COMMAND "AT+BAUD\r"
#define BLE_GET_NAME_COMMAND "AT+NAME\r"
#define BLE_GET_MODULE_PARAMETER_COMMAND "AT+RX\r"

#define BLE_SET_MAC_COMMAND "AT+ADDR="					// AT + ADDR = 123456789ABC \ r
#define BLE_SET_BOUD_COMMAND "AT+BAUD="					// AT + BAUD = 19200 \ r  [1200/2400/4800/9600/14400/19200/28800/38400/57600/76800/115200/230400]
#define BLE_SET_NAME_COMMAND "AT+NAME=" 				// AT + NAME = Wireless-tag01 \ r
#define BLE_SET_TRANSMIT_POWER_COMMAND "AT+RFPM=" 		// AT + RFPM = ble_transmit_power_t \ r
#define BLE_SET_SERIAL_NUMBER_COMMAND "AT+PID=" 		// AT + PID = ABCD \ r
#define BLE_SET_BROADCAST_INTERVAL_COMMAND "AT+ADP="	// AT + ADP = 500 \ r [100ms-4000ms]

#define BLE_SET_BROADCAST_DATA_COMMAND "AT+ADD=" 		// AT + ADD = 0123456A \ r max 16 bytes
// [Service UUID: 0x1234]
//	for ANDROID WRITE 0x1235: Write without response

#define BLE_RECEIVED_DO_NOTHING 0x01
#define BLE_RECEIVED_AUTO_MANUAL 0x02
#define BLE_RECEIVED_MOVEMENT 0x03
#define BLE_TRANSMIT_TEMPERATURE 0x04
#define BLE_TRANSMIT_X 0x05
#define BLE_TRANSMIT_Y 0x06
#define BLE_TRANSMIT_Z 0x07
#define BLE_TRANSMIT_ULTRASOUND 0x08
#define BLE_RECEIVED_ULTRASOUND_CONFIG 0x09

typedef enum {

	evgroup_ble_evbit_received = 0, evgroup_ble_evbit_N,

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

typedef enum {
	ble_received = 0, ble_transmit,
} ble_traffic;

typedef struct {
	ble_traffic info;
	char command;
	char valueReg1; // MSB
	char valueReg2; // LSB
//	char valueReg3;
//	char valueReg4; // LSB
} xQueueBleData;

/**
 *
 * @param command what you want to send as string
 * @return true is correctly
 */
bool ble_send_command(char *command, uint16_t size);

/**
 *
 * @param pData Received data
 * @return true when correctly
 */
bool ble_receive_command(/*char command,*/char *pData);

/**
 *
 * @param pData received data
 * @return true when correctly
 */
bool ble_receive_data(char *pData);

/**
 *
 * @param pData data to send
 * @param size od pData
 * @return true when correctly
 */
bool ble_send_data(char *pData, int size);

void ble_send_queue(xQueueBleData *data, ble_evgroup_bits_t evbit);

/**
 *
 * @return true when initialized
 */
bool ble_init(void);

/**
 *
 * @return true otherwise false if not OK
 */
bool ble_test_command(void);

/**
 *
 * @return return MAC address
 */
int ble_get_MAC_Address(void);

/**
 *
 * @param value MAC address
 * @return true
 */
bool ble_set_MAC(char *value);

/**
 *
 * @param value your BOUD
 * @return true
 */
bool ble_set_BOUD(int value);

/**
 *
 * @return (int) BOUD
 */
int ble_get_BOUD(void);
// char * name = (char*) malloc(sizeof(char) * 10);
// char[0] = 'x';
// char[1] = 'd';
// char[2] = '\0';
// strcpy(name, 'xd');
// free(name);

/**
 *
 * @param name
 * @return true
 */
bool ble_set_device_name(char *name);

/**
 *
 * @param buff received device name
 * @return true
 */
bool ble_get_device_name(char *buff);

/**
 *
 * @param power ble_transmit_power_t your power
 * @return true
 */
bool ble_set_transmit_power(ble_transmit_power_t power);

/**
 *
 * @return true
 */
bool ble_reset_module(void);

/**
 *
 * @return true
 */
bool ble_restore_default_values(void);

/**
 *
 * @param data your data to send
 * @return true
 */
bool ble_broadcast_data(char *data);

//bool ble_set_customized_MAC_address_

/**
 *
 * @param ms
 * @return true
 */
bool ble_set_broadcast_interval(int ms);

/**
 *
 * @param ms An active Bluetooth connection interval is 20ms-2000ms
 * @return
 */
bool ble_reset_interval(int ms);
/**
 *
 * @return true
 */
bool ble_low_power_sleep_mode(void);

/// CALLBACK FROM ISR
void timer_BLE(TimerHandle_t xTimer);
void timer_sent_test_BLE(TimerHandle_t xTimer);
#endif /* APPLICATION_MODULES_BLUETOOTH_LOW_ENERGY_BLUETOOTH_LE_H_ */
