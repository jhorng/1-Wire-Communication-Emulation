#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

#include "event.h"

typedef int (*EventCallbackFunc)(Event *evt);
typedef struct{
  EventCallbackFunc ongoing;
  EventCallbackFunc next;
}EventCallback;

typedef enum{
	IDLE_STATE,
	RESET_STATE,
	RESPONSE_STATE,
	FINISH_INIT_STATE
	// COMMAND_STATE,
	// READ_SLOT_STATE
}State;

typedef enum{
  SEARCH_BIT_STATE,
  BIT_DIRECTION_STATE,
  SEARCH_DONE_STATE
}SearchState;

typedef struct BitSearchingInfo BitSearchingInfo;
struct BitSearchingInfo{
	State state;
  SearchState searchState;
};

int bitSearchingFSM(Event evt);
int searchRomSM(Event evt);
void installCallbacks(EventCallback *evtCallbk, EventCallbackFunc ongoing, EventCallbackFunc next);

#endif // _STATE_MACHINE_H
