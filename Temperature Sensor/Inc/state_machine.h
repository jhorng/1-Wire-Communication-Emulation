/*
 * state_machine.h
 *
 *  Created on: Jul 3, 2017
 *      Author: Prince
 */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "event.h"

typedef enum{
	IDLE_STATE,
	RESET_STATE,
	RESPONSE_STATE,
	COMMAND_STATE
}State;

typedef struct BitSearchingInfo BitSearchingInfo;
struct BitSearchingInfo{
	State state;
	uint8_t data1;
	uint8_t data2;
	uint8_t data3;
	uint8_t data4;
	uint8_t data5;
	uint8_t data6;
	uint8_t data7;
	uint8_t data8;
};

void bitSearchingFSM(Event evt);

#endif /* STATE_MACHINE_H */
