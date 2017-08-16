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
  huart1.State = HAL_UART_STATE_BUSY;

  /*-------------------------- USART CR1 Configuration -----------------------*/
  /* Clear TE and RE bits */
  /* Enable the USART's transmit and receive interface by setting the TE and RE bit in the USART CR1 register */
  MODIFY_REG(huart1.Instance->CR1, (uint32_t)(USART_CR1_TE | USART_CR1_RE), USART_CR1_TE | USART_CR1_RE);

  huart1.State = HAL_UART_STATE_READY;

}
