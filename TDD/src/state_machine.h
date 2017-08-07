#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

#include "event.h"

typedef enum{
	IDLE_STATE,
	RESET_STATE,
	RESPONSE_STATE,
	FINISH_INIT_STATE,
	COMMAND_STATE,
	READ_SLOT_STATE
}State;

typedef struct BitSearchingInfo BitSearchingInfo;
struct BitSearchingInfo{
	State state;
};

void bitSearchingFSM(Event evt);

#endif // _STATE_MACHINE_H
