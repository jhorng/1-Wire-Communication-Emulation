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
	switch(state){
	case INIT_STATE:
		oneWireReset();
		state = RESPONSE_STATE;
		break;
	case RESPONSE_STATE:
		searchROM();
		state = INIT_STATE;
		break;
	default:
		state = INIT_STATE;
	}
	return state;
}

