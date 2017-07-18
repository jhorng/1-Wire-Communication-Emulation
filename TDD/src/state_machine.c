#include <stdlib.h>
#include <stdio.h>
#include "state_machine.h"

BitSearchingInfo bsi = {IDLE_STATE, 12, 42};

void BitSearchingFSM(Event evt){
  switch(bsi.state){
  case IDLE_STATE:
    if(evt == START_EVT){
      bsi.state = RESET_STATE;
    }
    break;
  case RESET_STATE:
    if(evt == UART_TX_CPL_EVT){
      bsi.state = RESPONSE_STATE;
    }
    else{
      bsi.state = RESET_STATE;
    }
    break;
  case RESPONSE_STATE:
		if(evt == UART_RX_CPL_EVT){
			bsi.state = COMMAND_STATE;
		}
		else{
			bsi.state = RESET_STATE;
		}
		break;
	case COMMAND_STATE:
		bsi.state = RESET_STATE;
		break;
	default:
		bsi.state = RESET_STATE;
  }
}