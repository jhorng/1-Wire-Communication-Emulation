/*
 * state_machine.h
 *
 *  Created on: Jul 3, 2017
 *      Author: Jaan Horng
 */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "event.h"

typedef enum{
	IDLE_STATE,
	RESET_STATE,
	RESPONSE_STATE,
	COMMAND_STATE,
	READ_SLOT_STATE
}OneWireState;

typedef struct OneWireInfo OneWireInfo;
struct OneWireInfo{
	OneWireState owState;  
};

int oneWireSM(Event evt);
void logSystemError(char *errMessage);

#endif /* STATE_MACHINE_H */
