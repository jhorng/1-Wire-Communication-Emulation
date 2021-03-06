/*
 * owState_machine.c
 *
 *  Created on: Jul 3, 2017
 *      Author: Jaan Horng
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "state_machine.h"
#include "event.h"
#include "hardware_interface.h"

OneWireInfo owInfo = {IDLE_STATE};
uint8_t presencePulse;
uint8_t responsePulse[72] = {0};
char regisNum[64] = {0};
volatile int i, j=0;

/*
 * @brief	To print out the error message for
 * 			the respective state.
 */
void logSystemError(char *errMessage){
  printf("%s\n", errMessage);
}

/*
 * @brief	This state machine will talk to the
 * 			sensor and obtain the registration number.
 * @param 	evt: Event received from the user as starter
 * 				 and callbacks.
 * @retval	status
 */
int oneWireSM(Event evt){
	switch(owInfo.owState){
	case IDLE_STATE:
		switch(evt){
      case START_EVT:
        halfDuplex_EnableTxRx();
        timerStart();
        owReceive(&presencePulse, sizeof(presencePulse));
        resetPulse();
        owInfo.owState = RESET_STATE;
        return 1;
      default:
        logSystemError("Received an unexpected event in oneWireSM::IDLE_STATE");
        return 1;
    }
		break;
    
	case RESET_STATE:
	  switch(evt){
      case UART_TX_CPL_EVT:
        owInfo.owState = RESET_STATE;	// buffer purpose for presence pulse to be received.
        return 1;
      case UART_RX_CPL_EVT:
        owInfo.owState = RESPONSE_STATE;
        return 1;
      case TIMEOUT_EVT:
        logSystemError("Timer has timeout before UART has received the data::RESET_STATE");
        owInfo.owState = IDLE_STATE;
        return 1;
      default:
        logSystemError("Received an unexpected event in oneWireSM::RESET_STATE");
        owInfo.owState = IDLE_STATE;
        return 1;
    }
		break;
    
	case RESPONSE_STATE:
    switch(evt){
      case TIMEOUT_EVT:
        timerStop();
        owReceive(responsePulse, sizeof(responsePulse));
        readROM();
        owInfo.owState = COMMAND_STATE;
        return 1;
      default:
        logSystemError("Received an unexpected event in oneWireSM::RESPONSE_STATE");
        owInfo.owState = IDLE_STATE;
        return 1;
    }
		break;
    
	case COMMAND_STATE:
    switch(evt){
      case UART_TX_CPL_EVT:	// Read slot should send right after the rom command.
        owReadSlot();		// Thus, command state should send read slot to sensor when command state receives UART_TX_CPL_EVT.
        owInfo.owState = READ_SLOT_STATE;
        return 1;
      default:
        logSystemError("Received an unexpected event in oneWireSM::COMMAND_STATE");
        owInfo.owState = IDLE_STATE;
        return 1;
		}
		break;
    
	case READ_SLOT_STATE:
		switch(evt){
      case UART_RX_CPL_EVT:
        for(i=71; i>7; i--){
          if(responsePulse[i] == 0xf8){
            regisNum[j] = '0';
          }
          else if(responsePulse[i] == 0xff){
            regisNum[j] = '1';
          }
          else{
            break;
          }
          j++;
        }
        printf("ID number: %s\n", regisNum);
        break;
      default:
        logSystemError("Received an unexpected event in oneWireSM::READ_SLOT_STATE");
        owInfo.owState = IDLE_STATE;
    }
    return 1;
		break;
    
	default:
    logSystemError("oneWireSM has received an unexpected state");
		owInfo.owState = IDLE_STATE;
	}
  return 0;
}
