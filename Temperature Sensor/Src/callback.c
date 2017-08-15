/*
 * timer.c
 *
 *  Created on: Jul 18, 2017
 *      Author: Jaan Horng
 */

#include "stm32f1xx_hal.h"
#include "state_machine.h"
#include "event.h"

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	oneWireSM(UART_TX_CPL_EVT);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	oneWireSM(UART_RX_CPL_EVT);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	oneWireSM(TIMEOUT_EVT);
}
