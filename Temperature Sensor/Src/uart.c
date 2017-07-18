/*
 * uart.c
 *
 *  Created on: Jul 18, 2017
 *      Author: TARUC
 */
#include "stm32f1xx_hal.h"
#include "uart.h"


HAL_StatusTypeDef HAL_HalfDuplex_EnableTxRx(UART_HandleTypeDef *huart){
  /* Process Locked */
  __HAL_LOCK(huart);

  huart->State = HAL_UART_STATE_BUSY;

  /*-------------------------- USART CR1 Configuration -----------------------*/
  /* Clear TE and RE bits */
  /* Enable the USART's transmit interface by setting the TE bit in the USART CR1 register */
  MODIFY_REG(huart->Instance->CR1, (uint32_t)(USART_CR1_TE | USART_CR1_RE), USART_CR1_TE | USART_CR1_RE);

  huart->State = HAL_UART_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(huart);

  return HAL_OK;
}
