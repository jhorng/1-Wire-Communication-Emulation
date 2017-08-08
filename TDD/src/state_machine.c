#include <stdlib.h>
#include <stdio.h>
#include "state_machine.h"
#include "functions.h"
#include "event.h"
#include "uart.h"
#include "timer.h"

UART_HandleTypeDef huart1;
TIM_HandleTypeDef htim2;

EventCallback timer2Callback = {NULL, NULL};
EventCallback uart1Callback = {NULL, NULL};

BitSearchingInfo bsi = {IDLE_STATE, SEARCH_BIT_STATE};
uint8_t reset = 0xE0;
uint8_t presencePulse;
uint8_t responsePulse[100] = {0};
char regisNum[64] = {0};
volatile int i, j=0;

int bitSearchingFSM(Event evt){
	switch(bsi.state){
	case IDLE_STATE:
		if(evt == START_EVT){
			HAL_HalfDuplex_EnableTxRx(&huart1);
			timerStart(&htim2);
			HAL_UART_Receive_IT(&huart1, &presencePulse, sizeof(presencePulse));
			resetPulse();
			bsi.state = RESET_STATE;
		}
		break;
	case RESET_STATE:
		if(evt == UART_TX_CPL_EVT){
			bsi.state = RESPONSE_STATE;
		}
		else{
			bsi.state = IDLE_STATE;
		}
		break;
	case RESPONSE_STATE:
		if(evt == UART_RX_CPL_EVT){
			bsi.state = FINISH_INIT_STATE;
		}
		else
			bsi.state = IDLE_STATE;
		break;
	case FINISH_INIT_STATE:
		if(evt == TIMEOUT_EVT){
			timerStop(&htim2);
			HAL_UART_Receive_IT(&huart1, responsePulse, sizeof(responsePulse));
			readROM();
			// bsi.state = COMMAND_STATE;
		}
    else
      bsi.state = IDLE_STATE;
		break;
	// case COMMAND_STATE:
		// if(evt == UART_TX_CPL_EVT){
			// masterReadSlot();
			// bsi.state = READ_SLOT_STATE;
		// }
		// else
			// bsi.state = IDLE_STATE;
		// break;
	// case READ_SLOT_STATE:
		// for(i=71; i>7; i--){
			// if(responsePulse[i] == 0xf8){
				// regisNum[j] = '0';
			// }
			// else if(responsePulse[i] == 0xff){
				// regisNum[j] = '1';
			// }
			// else{
				// break;
			// }
			// j++;
		// }
		// printf("ID number: %s\n", regisNum);
		// break;
	default:
		bsi.state = RESET_STATE;
	}
}

int searchRomSM(Event evt){
  switch(bsi.state){
  case SEARCH_BIT_STATE:
    if(evt == UART_TX_CPL_EVT){
      HAL_UART_Receive_IT(&huart1, responsePulse, sizeof(responsePulse));
			masterReadSlot();
			bsi.state = BIT_DIRECTION_STATE;
		}
    break;
  case BIT_DIRECTION_STATE:
    if(responsePulse[0] == 0xf8 && responsePulse[1] == 0xf8){
      masterWriteSlot(BYTE0);
      bsi.state = SEARCH_BIT_STATE;
    }
    else if(responsePulse[0] == 0xf8 && responsePulse[1] == 0xff){
      masterWriteSlot(BYTE0);
      bsi.state = SEARCH_BIT_STATE;
    }
    else if(responsePulse[0] == 0xff && responsePulse[1] == 0xf8){
      masterWriteSlot(BYTE1);
      bsi.state = SEARCH_BIT_STATE;
    }
    else{
      bsi.state = SEARCH_BIT_STATE;
    }
    break;
  case SEARCH_DONE_STATE:
    return 1;
    break;
  default:
    bsi.state = SEARCH_BIT_STATE;
  }
}



