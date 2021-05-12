/*
 * utility.c
 *
 *  Created on: 12 maj 2021
 *      Author: Arkadiusz
 */

#include "utility.h"

int u2_to_decimal(uint8_t u2) {

	char value = 0;

	if (u2 & (1 << 7)) {

		value = u2;
		value = ~value;
		value += 1;
		return (int) -value;

	} else {
		value = u2;
		return (int) value;
	}

}
