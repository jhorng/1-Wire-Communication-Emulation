/*
 * bs_state_machine.c
 *
 *  Created on: Aug 22, 2017
 *      Author: Jaan Horng
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "bs_state_machine.h"
#include "ow_state_machine.h"
#include "event.h"
#include "hardware_interface.h"

BitSearchInfo bsInfo = {COMMAND_STATE};
uint8_t responsePulse[2] = {0};

int bitSearchSM(Event evt){
  switch(bsInfo.bsState){
    case COMMAND_STATE:
      switch(evt){
        case START_EVT:
          // owReceive(responsePulse, sizeof(responsePulse));
          searchROM();
          bsInfo.bsState = BIT_SEARCH_STATE;
          return 1;
        default:
          logSystemError("Received an unexpected event in bitSearchSM::COMMAND_STATE");
          bsInfo.bsState = COMMAND_STATE;
          return 1;
      }
      break;
    case BIT_SEARCH_STATE:
      switch(evt){
        case UART_TX_CPL_EVT:
          owReceive(responsePulse, sizeof(responsePulse));
          owReadSlot(_2Bytes);
          bsInfo.bsState = BIT_SELECT_STATE;
          return 1;
        default:
          logSystemError("Received an unexpected event in bitSearchSM::BIT_SEARCH_STATE");
          bsInfo.bsState = COMMAND_STATE;
      }
      break;
    case BIT_SELECT_STATE:
      switch(evt){
        case UART_RX_CPL_EVT:
          if(responsePulse[0] == 0xf8 && responsePulse[1] == 0xf8){
            owTransmit(BYTE0, _1Byte);
          }
          else if(responsePulse[0] == 0xf8 && responsePulse[1] == 0xff){
            owTransmit(BYTE0, _1Byte);
          }
          else if(responsePulse[0] == 0xff && responsePulse[1] == 0xf8){
            owTransmit(BYTE1, _1Byte);
          }
          else{
            logSystemError("No device was found!");
          }
          return 1;
        default:
          logSystemError("Received an unexpected event in bitSearchSM::BIT_SELECT_STATE");
          return 1;
      }
      break;
    default:
      bsInfo.bsState = COMMAND_STATE;
  }
  return 0;
}

