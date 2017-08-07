#include "timer.h"
#include "uart.h"








HAL_StatusTypeDef HAL_HalfDuplex_EnableTxRx(UART_HandleTypeDef *huart);

void timerStart(TIM_HandleTypeDef *htim);

void timerStop(TIM_HandleTypeDef *htim);

void masterReadSlot();

HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

void resetPulse();

void presencePulseDetect();

void searchROM();

void readROM();

void skipROM();

void readPowerSupply();

void HAL_TIM_Base_Start_IT();
