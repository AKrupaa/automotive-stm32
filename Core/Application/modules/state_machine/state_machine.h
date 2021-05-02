/*
 * state_machine.h
 *
 *  Created on: May 2, 2021
 *      Author: Arkadiusz
 */

#ifndef APPLICATION_MODULES_STATE_MACHINE_STATE_MACHINE_H_
#define APPLICATION_MODULES_STATE_MACHINE_STATE_MACHINE_H_

typedef enum {

	evgroup_state_m_do_nothing = 1,
	evgroup_state_m_auto_manual = 2,
	evgroup_state_m_right = 4,
	evgroup_state_m_forward = 8,
	evgroup_state_m_left = 16,
	evgroup_state_m_back = 32,
	evgroup_state_m__evbit_N,

} state_machine_evgroup_bits_t;

#endif /* APPLICATION_MODULES_STATE_MACHINE_STATE_MACHINE_H_ */
