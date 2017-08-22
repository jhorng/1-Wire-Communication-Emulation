/*
 * hardware_interface.c
 *
 *  Created on: Jul 3, 2017
 *      Author: Jaan Horng
 */
#include <stdlib.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "hardware_interface.h"

extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim2;

void halfDuplex_EnableTxRx(){
  huart1.State = HAL_UART_STATE_BUSY;

  /*-------------------------- USART CR1 Configuration -----------------------*/
  /* Clear TE and RE bits */
  /* Enable the USART's transmit and receive interface by setting the TE and RE bit in the USART CR1 register */
  MODIFY_REG(huart1.Instance->CR1, (uint32_t)(USART_CR1_TE | USART_CR1_RE), USART_CR1_TE | USART_CR1_RE);

  huart1.State = HAL_UART_STATE_READY;
}

/*
 * @brief	To start the timer2.
 */
void timerStart(int period){
	HAL_GPIO_WritePin(amberLed_GPIO_Port, amberLed_Pin, GPIO_PIN_SET);
	htim2.Instance->ARR = period-1;
	htim2.Instance->CNT = 0;
	__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_GPIO_WritePin(amberLed_GPIO_Port, amberLed_Pin, GPIO_PIN_RESET);
}

/*
 * @brief	To stop the timer2.
 */
void timerStop(){
	HAL_GPIO_WritePin(amberLed_GPIO_Port, amberLed_Pin, GPIO_PIN_SET);
	HAL_TIM_Base_Stop_IT(&htim2);
	HAL_GPIO_WritePin(amberLed_GPIO_Port, amberLed_Pin, GPIO_PIN_RESET);
}

/*
 * @brief	To transmit the amount of size of data with the baud rate of 150kbps
 * @param	pData: pointer to the data
 * 		 	dataSize: Size of the data
 */
void owTransmit(uint8_t *pData, int dataSize){
	huart1.Instance->BRR = 480;

    HAL_UART_Transmit_IT(&huart1, pData, dataSize);
}

/*
 * @brief	To receive the amount of size of data with the baud rate of 150kbps
 * @param	pData: pointer to the data
 * 		 	dataSize: Size of the data
 */
void owReceive(uint8_t *pData, int dataSize){
	huart1.Instance->BRR = 480;

	HAL_UART_Receive_IT(&huart1, pData, dataSize);
}

/*
 * @brief	Transmit the reset pulse(0xE0) to the sensor with the baud rate of 11.538kbps.
 */
void resetPulse(){
	uint8_t reset = 0xE0;

	huart1.Instance->BRR = 6240;

	HAL_UART_Transmit_IT(&huart1, &reset, sizeof(reset));
}

/*
 * @brief	Receive the reset pulse with the presence pulse sent by the sensor with the baud rate of 11.538kbps.
 */
void presencePulseDetect(){
	uint8_t presencePulse=0;

	huart1.Instance->BRR = 6240;

	HAL_UART_Receive_IT(&huart1, &presencePulse, sizeof(presencePulse));
}

/*
 * @brief	This function is to send a data (F0h) to the
 * 			sensor to search the registration number of
 * 			the sensor bit by bit, till the 64th bit of
 * 			the registration number.
 */
void searchROM(){
	uint8_t searchCommand[] = {BYTE0, BYTE0, BYTE0, BYTE0, BYTE1, BYTE1, BYTE1, BYTE1};

	owTransmit(searchCommand, sizeof(searchCommand));
}

/*
 * @brief	This function is to send a data (33h) to the
 * 			sensor to obtain the registration number of the
 * 			sensor, if and only if one device is connected
 * 			to the master. Otherwise, error will occur.
 */
void readROM(){
	uint8_t readCommand[] = {BYTE1, BYTE1, BYTE0, BYTE0, BYTE1, BYTE1, BYTE0, BYTE0};

	owTransmit(readCommand, sizeof(readCommand));
}

/*
 * @brief	This rom command will skip the handshaking process like the process of search command and read command.
 */
void skipROM(){
	uint8_t skipCommand[] = {BYTE0, BYTE0, BYTE1, BYTE1, BYTE0, BYTE0, BYTE1, BYTE1};

	owTransmit(skipCommand, sizeof(skipCommand));
}

/*
 * brief	To distinguish the power supplies to the sensor.
 */
void readPowerSupply(){
	uint8_t readPowSupCommand[] = {BYTE0, BYTE0, BYTE1, BYTE0, BYTE1, BYTE1, BYTE0, BYTE1};

	owTransmit(readPowSupCommand, sizeof(readPowSupCommand));
}

/*
 * @brief	To acknowledge the sensor to response.
 */
void owReadSlot(){
	int i=0;
	uint8_t txData[64] = {0};

	for(i=0; i<64; i++){
		txData[i] = BYTE1;
	}

	owTransmit(txData, sizeof(txData));
}
