/*
 * utility.c
 *
 *  Created on: 12 maj 2021
 *      Author: Arkadiusz
 */

#include "utility.h"
#include <math.h>
#include "stdlib.h"

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

uint16_t int16_to_u2(int16_t decimal) {
	uint16_t u2 = 0;

	if (decimal >= 0) {
		u2 = (uint16_t) decimal;
	} else {
		u2 = (uint16_t) abs(decimal);
		u2 = (uint16_t) ~u2;
		u2 += 1;
	}

	return u2;
}
