/*
 * uart.c
 *
 *  Created on: Jul 18, 2017
 *      Author: Jaan Horng
 */
#include "stm32f1xx_hal.h"
#include "uart.h"

extern UART_HandleTypeDef huart1;

void halfDuplex_EnableTxRx(){
  /* Process Locked */
  //__HAL_LOCK(&huart1);

  huart1.State = HAL_UART_STATE_BUSY;

  /*-------------------------- USART CR1 Configuration -----------------------*/
  /* Clear TE and RE bits */
  /* Enable the USART's transmit interface by setting the TE bit in the USART CR1 register */
  MODIFY_REG(huart1.Instance->CR1, (uint32_t)(USART_CR1_TE | USART_CR1_RE), USART_CR1_TE | USART_CR1_RE);

  huart1.State = HAL_UART_STATE_READY;

  /* Process Unlocked */
  //__HAL_UNLOCK(&huart1);

  //return HAL_OK;
}
