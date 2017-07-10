/*
 * state_machine.c
 *
 *  Created on: Jul 3, 2017
 *      Author: Prince
 */
#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include "state_machine.h"
#include "function.h"

UART_HandleTypeDef huart1;

int fsm(State state){
	//static uint8_t	rxData[100] = {0};
	uint8_t bit0 = BYTE0;
	switch(state){
	case INIT:
		oneWireReset();
		state = SEARCH;
		break;
	case SEARCH:
		skipROM();
		readPowerSupply();
		searchROM();
		//readROM();
		//HAL_UART_Receive(&huart1, rxData, sizeof(rxData), 0);
		state = RECEIVE;
		break;
	case RECEIVE:
		masterWriteByteWithInterrupt(&bit0, sizeof(bit0));
		break;
	default:
		state = INIT;
	}
	return state;
}

