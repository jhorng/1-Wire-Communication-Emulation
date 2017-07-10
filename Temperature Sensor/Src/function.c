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

void masterWriteByteWithInterrupt(uint8_t *byte, int dataSize){
	if(*byte == BYTE0){
		huart1.Instance->BRR = 480;
	}
	else if(*byte == BYTE1){
		huart1.Instance->BRR = 432;
	}
	else{
		huart1.Instance->BRR = 625;
	}

	HAL_UART_Transmit(&huart1, byte, dataSize, 0);
}

void oneWireReset(){
	uint8_t reset = 0x00;

	huart1.Instance->BRR = 4000;

	HAL_UART_Transmit(&huart1, &reset, sizeof(reset), 0);
}

/*
 * @brief	This function is to send a data (F0h) to the
 * 			sensor to search the registration number of
 * 			the sensor bit by bit, till the 64th bit of
 * 			the registration number.
 */
void searchROM(){
	uint8_t bit0 = BYTE0;
	uint8_t bit1 = BYTE0;
	uint8_t bit2 = BYTE0;
	uint8_t bit3 = BYTE0;
	uint8_t bit4 = BYTE1;
	uint8_t bit5 = BYTE1;
	uint8_t bit6 = BYTE1;
	uint8_t bit7 = BYTE1;

	masterWriteByteWithInterrupt(&bit0, sizeof(bit0));
	masterWriteByteWithInterrupt(&bit1, sizeof(bit1));
	masterWriteByteWithInterrupt(&bit2, sizeof(bit2));
	masterWriteByteWithInterrupt(&bit3, sizeof(bit3));
	masterWriteByteWithInterrupt(&bit4, sizeof(bit4));
	masterWriteByteWithInterrupt(&bit5, sizeof(bit5));
	masterWriteByteWithInterrupt(&bit6, sizeof(bit6));
	masterWriteByteWithInterrupt(&bit7, sizeof(bit7));
}

/*
 * @brief	This function is to send a data (33h) to the
 * 			sensor to obtain the registration number of the
 * 			sensor, if and only if one device is connected
 * 			to the master. Otherwise, error will occur.
 */
void readROM(){
	uint8_t bit0 = BYTE1;
	uint8_t bit1 = BYTE1;
	uint8_t bit2 = BYTE0;
	uint8_t bit3 = BYTE0;
	uint8_t bit4 = BYTE1;
	uint8_t bit5 = BYTE1;
	uint8_t bit6 = BYTE0;
	uint8_t bit7 = BYTE0;

	masterWriteByteWithInterrupt(&bit0, sizeof(bit0));
	masterWriteByteWithInterrupt(&bit1, sizeof(bit1));
	masterWriteByteWithInterrupt(&bit2, sizeof(bit2));
	masterWriteByteWithInterrupt(&bit3, sizeof(bit3));
	masterWriteByteWithInterrupt(&bit4, sizeof(bit4));
	masterWriteByteWithInterrupt(&bit5, sizeof(bit5));
	masterWriteByteWithInterrupt(&bit6, sizeof(bit6));
	masterWriteByteWithInterrupt(&bit7, sizeof(bit7));
}

void skipROM(){
	uint8_t bit0 = BYTE0;
	uint8_t bit1 = BYTE0;
	uint8_t bit2 = BYTE1;
	uint8_t bit3 = BYTE1;
	uint8_t bit4 = BYTE0;
	uint8_t bit5 = BYTE0;
	uint8_t bit6 = BYTE1;
	uint8_t bit7 = BYTE1;

	masterWriteByteWithInterrupt(&bit0, sizeof(bit0));
	masterWriteByteWithInterrupt(&bit1, sizeof(bit1));
	masterWriteByteWithInterrupt(&bit2, sizeof(bit2));
	masterWriteByteWithInterrupt(&bit3, sizeof(bit3));
	masterWriteByteWithInterrupt(&bit4, sizeof(bit4));
	masterWriteByteWithInterrupt(&bit5, sizeof(bit5));
	masterWriteByteWithInterrupt(&bit6, sizeof(bit6));
	masterWriteByteWithInterrupt(&bit7, sizeof(bit7));
}

void readPowerSupply(){
	uint8_t bit0 = BYTE0;
	uint8_t bit1 = BYTE0;
	uint8_t bit2 = BYTE1;
	uint8_t bit3 = BYTE0;
	uint8_t bit4 = BYTE1;
	uint8_t bit5 = BYTE1;
	uint8_t bit6 = BYTE0;
	uint8_t bit7 = BYTE1;

	masterWriteByteWithInterrupt(&bit0, sizeof(bit0));
	masterWriteByteWithInterrupt(&bit1, sizeof(bit1));
	masterWriteByteWithInterrupt(&bit2, sizeof(bit2));
	masterWriteByteWithInterrupt(&bit3, sizeof(bit3));
	masterWriteByteWithInterrupt(&bit4, sizeof(bit4));
	masterWriteByteWithInterrupt(&bit5, sizeof(bit5));
	masterWriteByteWithInterrupt(&bit6, sizeof(bit6));
	masterWriteByteWithInterrupt(&bit7, sizeof(bit7));
}
