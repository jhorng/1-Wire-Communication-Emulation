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
uint8_t bitSelect=0;

int bitSearchSM(Event evt){
  switch(bsInfo.bsState){
    case COMMAND_STATE:
      switch(evt){
        case START_EVT:
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
          return 1;
      }
      break;
    case BIT_SELECT_STATE:
      switch(evt){
        case UART_RX_CPL_EVT:
          if(responsePulse[0] == 0xf8 && responsePulse[1] == 0xf8){
            bitSelect = BYTE0;
            owTransmit(&bitSelect, _1Byte);
            bsInfo.bsState = BIT_SEARCH_STATE;
          }
          else if(responsePulse[0] == 0xf8 && responsePulse[1] == 0xff){
            bitSelect = BYTE0;
            owTransmit(&bitSelect, _1Byte);
            bsInfo.bsState = BIT_SEARCH_STATE;
          }
          else if(responsePulse[0] == 0xff && responsePulse[1] == 0xf8){
            bitSelect = BYTE1;
            owTransmit(&bitSelect, _1Byte);
            bsInfo.bsState = BIT_SEARCH_STATE;
          }
          else{
            logSystemError("No device was found!");
            bsInfo.bsState = COMMAND_STATE;            
          }
          return 1;
        default:
          logSystemError("Received an unexpected event in bitSearchSM::BIT_SELECT_STATE");
          bsInfo.bsState = COMMAND_STATE;            
          return 1;
      }
      break;
    default:
      bsInfo.bsState = COMMAND_STATE;
  }
  return 0;
}

