#include <stdlib.h>
#include <stdio.h>
#include "state_machine.h"
#include "functions.h"

BitSearchingInfo bsi = {IDLE_STATE, 12, 42};

int buffer(int elem1, int elem2){
  int *ptr = (int *)malloc(2);
  ptr[0] = elem1;
  ptr[1] = elem2;
  return (int)ptr;
}

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

void HAL_UART_TxCpltCallback(){
  BitSearchingFSM(UART_TX_CPL_EVT);
}

void HAL_UART_RxCpltCallback(){
  BitSearchingFSM(UART_RX_CPL_EVT);
}