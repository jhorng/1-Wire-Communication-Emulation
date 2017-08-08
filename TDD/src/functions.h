#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdlib.h>
#include <stdint.h>
#include "uart.h"
#include "timer.h"

#define BYTE0 0x0
#define BYTE1 0xff

HAL_StatusTypeDef HAL_HalfDuplex_EnableTxRx(UART_HandleTypeDef *huart);
void timerStart(TIM_HandleTypeDef *htim);
void timerStop(TIM_HandleTypeDef *htim);
void masterReadSlot();
void masterWriteSlot(uint8_t bit);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
void resetPulse();
void presencePulseDetect();
void searchROM();
void readROM();
void skipROM();
void readPowerSupply();
void HAL_TIM_Base_Start_IT();

#endif // _FUNCTIONS_H
