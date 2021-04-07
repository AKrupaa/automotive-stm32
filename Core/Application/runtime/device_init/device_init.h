/*
 * device_init.h
 *
 *  Created on: Mar 27, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_RUNTIME_DEVICE_INIT_H_
#define APPLICATION_RUNTIME_DEVICE_INIT_H_

#include "stdbool.h"

void device_init(void);

typedef struct {
	bool (*init_function)(void);	///< Pointer to an init function.
	char const *name;					/// Module name.
	bool active;						///< Module init enable.
} module_t;

/* ************************************************************************** */

typedef enum {
	mod_0,
	mod_BLE = mod_0,
	mod_hall,
	mod_opto,
	mod_proximity,
	mod_H_bridge,
	mod_magnetometer,
	mod_eeprom,
	mod_servo,
	mod_N
} moduleName_t;

extern module_t modules_cfg[];

#endif /* APPLICATION_RUNTIME_DEVICE_INIT_H_ */
