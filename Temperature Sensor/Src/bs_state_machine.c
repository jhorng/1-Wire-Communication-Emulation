/*
 * bs_state_machine.c
 *
 *  Created on: Aug 22, 2017
 *      Author: Jaan Horng
 */

#include <stdlib.h>
#include "bs_state_machine.h"

BitSearchInfo bsInfo = {COMMAND_STATE};

int bitSearchSM(Event evt){
  switch(bsInfo.bsState){
    case COMMAND_STATE:
      return 1;
    case BIT_SEARCH_STATE:
      return 1;
    case BIT_SELECT_STATE:
      return 1;
    default:
      bsInfo.bsState = COMMAND_STATE;
  }
  return 0;
}
