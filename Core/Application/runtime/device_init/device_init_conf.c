/*
 * device_init_conf.c
 *
 *  Created on: Mar 28, 2021
 *      Author: Arkadiusz
 */

#include <ultrasound_sensor/ultrasound.h>
#include "device_init.h"
#include "bluetooth_low_energy/bluetooth_le.h"
#include "eeprom/eeprom.h"
#include "H_bridge/h_bridge.h"
#include "hall/hall.h"
#include "magnetometer/magnetometer.h"
#include "slotted_optocoupler/optocoupler.h"
#include "servo/servo.h"

module_t modules_cfg[] =
{
//		mod_BLE
	{
		.init_function = ble_init,
		.name = "BLUETOOTH LOW ENERGY MODULE",
		.active = true //this module should be enabled at the start of device init procedure
	},
	// mod_hall
	{
		.init_function = hall_init,
		.name = "HALL MODULE",
		.active = true
	},
	// mod_opto
	{
		.init_function = optocoupler_init,
		.name = "OPTOCOUPLER MODULE",
		.active = true
	},
	// mod_proximity
	{
		.init_function = ultrasound_init,
		.name = "ULTRASOUND MODULE",
		.active = true
	},
	// mod_H_bridge
	{
		.init_function = h_bridge_init,
		.name = "H BRIDGE MODULE",
		.active = true
	},
	// mod_magnetometer
	{
		.init_function = magnetometer_init,
		.name = "MAGNETOMETER MODULE",
		.active = true
	},
	// mod_eeprom
	{
		.init_function = eeprom_init,
		.name = "EEPROM MODULE",
		.active = true
	},
	// mod_servo
	{
		.init_function = servo_init,
		.name = "SERVO MODULE",
		.active = true
	},
};

