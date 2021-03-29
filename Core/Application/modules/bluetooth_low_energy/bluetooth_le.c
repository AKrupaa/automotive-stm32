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
const char its_OK[] = "OK\r";

/**
 *
 * @return true when initialized
 */
bool ble_init(void) {
	;

	//	OUT_BLE_EN;
	// high level closes the serial port
	// low level enables the serial port

	//	close
	//	HAL_GPIO_WritePin(OUT_BLE_EN_GPIO_Port, OUT_BLE_EN_Pin, GPIO_PIN_SET);
	//	turn on serial communication
	//	HAL_GPIO_WritePin(OUT_BLE_EN_GPIO_Port, OUT_BLE_EN_Pin, GPIO_PIN_RESET);
	ble_turn_off_transmittion;
	ble_turn_on_transmittion;

	bool status = ble_test_command();
	ble_turn_off_transmittion;

	if (status)
		return true;
	else
		return false;

}

/**
 *
 * @return true otherwise false if not OK
 */
bool ble_test_command(void) {

//	const char *OK = (char*) malloc(sizeof(char)*)

	char *pData = (char*) malloc(sizeof(char) * 4);

//	char *strcpy (char* strTo, const char* strFrom);

	strcpy(pData, "AT\r");

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) pData, strlen(pData),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		free(pData);
		return false;
	}

	ble_turn_off_transmittion;

	ble_turn_on_transmittion;

	if (HAL_UART_Receive(&huart3, (uint8_t*) pData, strlen(pData),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		free(pData);
		return false;
	}

	ble_turn_off_transmittion;

	if (strcmp(pData, its_OK) == 0) {
		free(pData);
		return true;
	} else {
		free(pData);
		return false;
	}

}

int ble_get_MAC_Address(void) {
	const char c_get_address[] = "AT + ADDR\r";

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) c_get_address,
			strlen(c_get_address),
			HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return 0;
	}

	ble_turn_off_transmittion;

	ble_turn_on_transmittion;

	char c_address[16];

	if (HAL_UART_Receive(&huart3, (uint8_t*) c_address, strlen(c_address),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return 0;
	}

	return atoi(c_address);
}

bool ble_set_MAC(int value) {
//	const char c_get_address[] = "AT + ADDR";
	char string_[16];
	sprintf(string_, "AT+ADDR=%d\r", value);

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) string_, strlen(string_),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return 0;
	}

	ble_turn_off_transmittion;
	ble_turn_on_transmittion;

	if (HAL_UART_Receive(&huart3, (uint8_t*) string_, strlen(string_),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return 0;
	}

	ble_turn_off_transmittion;

	if (strcmp(string_, its_OK) == 0) {
		return true;
	} else
		return false;

}

bool ble_set_BOUD(int value) {
//	AT + BAUD = 19200\r
	char set_string[16];
	sprintf(set_string, "AT+BAUD=%i\r", value);

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	ble_turn_on_transmittion;
	if (HAL_UART_Receive(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}

	ble_turn_off_transmittion;

//	int recived = atoi(set_string);

	if (strcmp(set_string, its_OK) == 0) {
		return true;
	} else
		return false;

}

int ble_get_BOUD(void) {
	//	AT + BAUD = 19200\r
	char set_string[16] = "AT+BAUD\r";
//		sprintf(set_string, "AT+BAUD=%i\r", value);

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	ble_turn_on_transmittion;
	if (HAL_UART_Receive(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}

	ble_turn_off_transmittion;

	int recived = atoi(set_string);
	return recived;
}

// char * name = (char*) malloc(sizeof(char) * 10);
// char[0] = 'x';
// char[1] = 'd';
// char[2] = '\0';
// strcpy(name, 'xd');
// free(name);
bool ble_set_device_name(char *name) {
	//	AT + BAUD = 19200\r
	char set_string[30];
	sprintf(set_string, "AT+NAME=%s\r", name);

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	ble_turn_on_transmittion;
	if (HAL_UART_Receive(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}

	ble_turn_off_transmittion;

//		int recived = atoi(set_string);
//		return recived;
	if (strcmp(set_string, its_OK) == 0) {
		return true;
	} else
		return false;
}

bool ble_get_device_name(char *buff) {

	//	AT + BAUD = 19200\r
	char set_string[30] = "AT+NAME\r";
//		sprintf(set_string, "AT+NAME=%s\r", name);

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	ble_turn_on_transmittion;
	if (HAL_UART_Receive(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}

	ble_turn_off_transmittion;

//		int recived = atoi(set_string);
//		buff = set_string;
	strcpy(buff, set_string);

	return true;
//		if (strcmp(set_string, its_OK) == 0) {
//			return true;
//		} else
//			return false;

}

bool ble_set_transmit_power(ble_transmit_power_t power) {
//	AT + RFPM = 3 \ r
	char set_string[16];
	sprintf(set_string, "AT+RFPM=%i\r", power);

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	ble_turn_on_transmittion;
	if (HAL_UART_Receive(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}

	ble_turn_off_transmittion;

	//		int recived = atoi(set_string);
	//		return recived;
	if (strcmp(set_string, its_OK) == 0) {
		return true;
	} else
		return false;
}

bool ble_reset_module(void) {
	//	AT + RESET \ r
	char set_string[16] = "AT+RESET\r";
//			sprintf(set_string, "AT+RFPM=%i\r", power);

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	ble_turn_on_transmittion;
	if (HAL_UART_Receive(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}

	ble_turn_off_transmittion;

	//		int recived = atoi(set_string);
	//		return recived;
	if (strcmp(set_string, its_OK) == 0) {
		return true;
	} else
		return false;
}

bool ble_restore_default_values(void) {
	char set_string[16] = "AT+DEFAULT\r";
//			sprintf(set_string, "AT+RFPM=%i\r", power);

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	ble_turn_on_transmittion;
	if (HAL_UART_Receive(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}

	ble_turn_off_transmittion;

	//		int recived = atoi(set_string);
	//		return recived;
	if (strcmp(set_string, its_OK) == 0) {
		return true;
	} else
		return false;
}

bool ble_broadcast_data(uint8_t *data, int size) {
	//	AT + RESET \ r
	uint8_t set_string[size + 8];
	sprintf(set_string, "AT+ADD=%s\r", data);

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	ble_turn_on_transmittion;
	if (HAL_UART_Receive(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}

	ble_turn_off_transmittion;

	//		int recived = atoi(set_string);
	//		return recived;
	if (strcmp(set_string, its_OK) == 0) {
		return true;
	} else
		return false;
}

//bool ble_set_customized_MAC_address_

bool ble_set_broadcast_interval(int interval_in_ms) {
	uint8_t set_string[16];
	sprintf(set_string, "AT+ADP=%i\r", interval_in_ms);

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	ble_turn_on_transmittion;
	if (HAL_UART_Receive(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}

	ble_turn_off_transmittion;

	//		int recived = atoi(set_string);
	//		return recived;
	if (strcmp(set_string, its_OK) == 0) {
		return true;
	} else
		return false;
}

bool ble_reset_interval(void) {
	uint8_t set_string[16] = "AT+CIT=300\r"
//	sprintf(set_string, "AT+ADD=%i\r", interval_in_ms);

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
	ble_turn_off_transmittion;
	ble_turn_on_transmittion;
	if (HAL_UART_Receive(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}

	ble_turn_off_transmittion;

	//		int recived = atoi(set_string);
	//		return recived;
	if (strcmp(set_string, its_OK) == 0) {
		return true;
	} else
		return false;
}

bool ble_low_power_sleep_mode(void) {
	uint8_t set_string[16] = "AT+SLEEP\r"
//	sprintf(set_string, "AT+ADD=%i\r", interval_in_ms);

	ble_turn_on_transmittion;
	if (HAL_UART_Transmit(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}
//		ble_turn_off_transmittion;
//		ble_turn_on_transmittion;
	if (HAL_UART_Receive(&huart3, (uint8_t*) set_string, strlen(set_string),
	HAL_MAX_DELAY) != HAL_OK) {
		ble_turn_off_transmittion;
		return false;
	}

	ble_turn_off_transmittion;

	//		int recived = atoi(set_string);
	//		return recived;
	if (strcmp(set_string, its_OK) == 0) {
		return true;
	} else
		return false;
}
