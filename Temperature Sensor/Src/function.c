/*
 * function.c
 *
 *  Created on: Jul 3, 2017
 *      Author: Prince
 */
#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include "function.h"

UART_HandleTypeDef huart1;

void masterWriteByte(uint8_t byte){
	static uint16_t size = 0x00FF;

	HAL_UART_Transmit(&huart1, &byte, size, 0);
}

void masterWriteByteWithInterrupt(uint8_t byte){
	static uint16_t size = 0x00FF;

	HAL_UART_Transmit_IT(&huart1, &byte, size);
}

void oneWireReset(){
	static uint8_t reset = 0x0;
	static uint16_t size = 0x00FF;

	HAL_UART_Transmit(&huart1, &reset, size, 0);
}

void searchCommand(){
	int i;

	for(i=0; i<9; i++){
		if(i<5){
			masterWriteByte(BYTE0);
		}
		else{
			masterWriteByte(BYTE1);
		}
	}
}

void readCommand(){
	masterWriteByteWithInterrupt(BYTE1);
	masterWriteByteWithInterrupt(BYTE1);
	masterWriteByteWithInterrupt(BYTE0);
	masterWriteByteWithInterrupt(BYTE0);
	masterWriteByteWithInterrupt(BYTE1);
	masterWriteByteWithInterrupt(BYTE1);
	masterWriteByteWithInterrupt(BYTE0);
	masterWriteByteWithInterrupt(BYTE0);
}
