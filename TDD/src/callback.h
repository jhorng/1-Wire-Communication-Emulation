#ifndef CALLBACK_H_
#define CALLBACK_H_

void HAL_UART_TxCpltCallback(int *huart);
void HAL_UART_RxCpltCallback(int *huart);
void HAL_TIM_PeriodElapsedCallback(int *htim);

#endif /* CALLBACK_H_ */