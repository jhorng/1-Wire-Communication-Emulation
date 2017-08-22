/*
 * bs_state_machine.h
 *
 *  Created on: Aug 22, 2017
 *      Author: Jaan Horng
 */

#ifndef BS_STATE_MACHINE_H_
#define BS_STATE_MACHINE_H_

#include "event.h"

typedef enum{
  COMMAND_STATE,
  BIT_SEARCH_STATE,
  BIT_SELECT_STATE
}BitSearchState;

typedef struct BitSearchInfo BitSearchInfo;
struct BitSearchInfo{
	BitSearchState bsState;
};

int bitSearchSM(Event evt);

#endif /* BS_STATE_MACHINE_H_ */
