/*
 * bluetooth_le.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#include "bluetooth_le.h"

// huart3 for BLE communication

// INTERRUPT IRQ_BLE 100us high-level pulse signal tips after received the primary-side data
///**
// *
// * @param GPIO_Pin
// */
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//
//	EventGroupHandle_t Evh = g_rt_evgroups[Ev];
//	EventBits_t msk = (1u << bit);
//
//}

/* file scope constant */
static const char its_OK[] = BLE_OK;
/* file scope */
//static char ble_pData[BLE_MAX_SIZE];

/*
 * PRIVATE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

bool ble_send_command(char *command, uint16_t size) {
	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) command, size, 100) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	return true;
}

bool ble_receive_command(/*char command,*/char *command) {
	ble_turn_on_transmittion;
//	if (HAL_UART_Transmit(&huart3, (uint8_t*) command, strlen(command), 100)
//			!= HAL_OK) {
//		ble_turn_off_transmittion;
//		return false;
//	}
//	int no = strlen(command);
	if (HAL_UART_Receive(&huart3, (uint8_t*) command, BLE_MAX_SIZE, 100)
			!= HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	return true;
}

/*
 * PUBLIC ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

bool ble_send_data(char *pData, int size) {
	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) pData, (uint16_t) size, 100) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	return true;
}

bool ble_receive_data(char *pData) {
	ble_turn_on_transmittion;
	uint16_t size = sizeof(pData);

	if (HAL_UART_Receive(&huart3, (uint8_t*) pData, size - 1, 1000) != HAL_OK) {
//		ble_turn_off_transmittion;
		return false;
	}
//	ble_turn_off_transmittion;
	return true;
}

void ble_send_queue(xQueueBleData *data, ble_evgroup_bits_t evbit) {

//	xQueueBleData bleData = { 0 };
	rt_enqueue(rt_queue_cos_tam_2, data);
//	rt_evbitset(rt_evgroup_Valve, evbit);
}

bool ble_init(void) {
//	ble_turn_off_transmittion;
//	ble_turn_on_transmittion;
//
//	bool status = ble_test_command();
//	ble_turn_off_transmittion;
//
//	if (status)
//		return true;
//	else
//		return false;
	return true;
}

bool ble_test_command(void) {

//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	int size = sprintf(buff, BLE_TEST_COMMAND);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

	memset(buff, 0, size);

	if (ble_receive_command(buff) != true) {
		return false;
	}

	if (strcmp(buff, its_OK) != 0) {
		return false;
	}

//	memset(pData, 0, MAX_SIZE);
	return true;
}

int ble_get_MAC_Address(void) {

//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	int size = sprintf(buff, BLE_GET_MAC_COMMAND);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

	memset(buff, 0, size);

	if (ble_receive_command(buff) != true) {
		return false;
	}

	return atoi(buff);
}

bool ble_set_MAC(char *value) {

//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	int size = sprintf(buff, "%s%s%s", BLE_SET_MAC_COMMAND, value, BLE_TERMINATOR);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

	memset(buff, 0, size);

	if (ble_receive_command(buff) != true) {
		return false;
	}

	if (strcmp(buff, its_OK) != 0) {
		return false;
	}

	return true;
}

bool ble_set_BOUD(int value) {

//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	int size = sprintf(buff, "%s%d%s", BLE_SET_BOUD_COMMAND, value, BLE_TERMINATOR);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

	memset(buff, 0, size);

	if (ble_receive_command(buff) != true) {
		return false;
	}

	if (strcmp(buff, its_OK) != 0) {
		return false;
	}

	return true;
}

int ble_get_BOUD(void) {
//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	int size = sprintf(buff, "%s", BLE_GET_BOUD_COMMAND);	//, value, BLE_TERMINATOR);
//	strcpy(pData, BLE_GET_MAC_COMMAND);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

	memset(buff, 0, size);

	if (ble_receive_command(buff) != true) {
		return false;
	}

	return atoi(buff);
}

bool ble_set_device_name(char *name) {
//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	int size = sprintf(buff, "%s%s%s", BLE_SET_NAME_COMMAND, name, BLE_TERMINATOR);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

//	memset(pData, 0, MAX_SIZE);

	if (ble_receive_command(buff) != true) {
		return false;
	}

	if (strcmp(buff, its_OK) != 0) {
		return false;
	}

	return true;
}

bool ble_get_device_name(char *buff) {

//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff2[20];
	int size = sprintf(buff2, "%s", BLE_GET_NAME_COMMAND);	//, name, BLE_TERMINATOR);

	if (ble_send_command(buff2,size) != true) {
		return false;
	}

	memset(buff2, 0, size);

	if (ble_receive_command(buff2) != true) {
		return false;
	}

	strcpy(buff, buff2);

	return true;
}

bool ble_set_transmit_power(ble_transmit_power_t power) {
//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	char value[4];

	itoa(power, value, 10);
	int size = sprintf(buff, "%s%s%s", BLE_SET_TRANSMIT_POWER_COMMAND, value,
	BLE_TERMINATOR);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

	memset(buff, 0, BLE_MAX_SIZE);

	if (ble_receive_command(buff) != true) {
		return false;
	}

	if (strcmp(buff, its_OK) != 0) {
		return false;
	}

	return true;
}

bool ble_reset_module(void) {
//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	int size = sprintf(buff, "%s", BLE_RESET_COMMAND);	//, power, BLE_TERMINATOR);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

	memset(buff, 0, size);

	if (ble_receive_command(buff) != true) {
		return false;
	}

	if (strcmp(buff, its_OK) != 0) {
		return false;
	}

	return true;
}

bool ble_restore_default_values(void) {
//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	int size = sprintf(buff, "%s", BLE_RESET_COMMAND);	//, power, BLE_TERMINATOR);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

	memset(buff, 0, size);

	if (ble_receive_command(buff) != true) {
		return false;
	}

	if (strcmp(buff, its_OK) != 0) {
		return false;
	}

	return true;
}

bool ble_broadcast_data(char *data) {
//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	int size = sprintf(buff, "%s%s%s", BLE_SET_BROADCAST_DATA_COMMAND, data,
	BLE_TERMINATOR);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

	memset(buff, 0, size);

	if (ble_receive_command(buff) != true) {
		return false;
	}

	if (strcmp(buff, its_OK) != 0) {
		return false;
	}

	return true;
}

bool ble_set_broadcast_interval(int ms) {
//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	int size = sprintf(buff, "%s%d%s", BLE_SET_BROADCAST_INTERVAL_COMMAND, ms,
	BLE_TERMINATOR);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

	memset(buff, 0, size);

	if (ble_receive_command(buff) != true) {
		return false;
	}

	if (strcmp(buff, its_OK) != 0) {
		return false;
	}

	return true;
}

bool ble_reset_interval(int ms) {
//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	int size = sprintf(buff, "%s%d%s", BLE_SET_BROADCAST_INTERVAL_COMMAND,
			ms, BLE_TERMINATOR);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

	memset(buff, 0, size);

	if (ble_receive_command(buff) != true) {
		return false;
	}

	if (strcmp(buff, its_OK) != 0) {
		return false;
	}

	return true;
}

bool ble_low_power_sleep_mode(void) {
//	memset(ble_pData, 0, BLE_MAX_SIZE);
	char buff[20];
	int size = sprintf(buff, "%s", BLE_LOW_POWER_MODE_COMMAND);//, ms, BLE_TERMINATOR);
	//	strcpy(pData, BLE_GET_MAC_COMMAND);

	if (ble_send_command(buff, size) != true) {
		return false;
	}

	memset(buff, 0, size);

	if (ble_receive_command(buff) != true) {
		return false;
	}

//	strcpy(buff, pData);

	if (strcmp(buff, its_OK) != 0) {
		return false;
	}

	return true;

	//	if (value != atoi(pData)) {
	//		return false;
	//	}

	//	return atoi(pData);
}
