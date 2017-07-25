/*
 * timer.c
 *
 *  Created on: Jul 18, 2017
 *      Author: TARUC
 */

#include "stm32f1xx_hal.h"
#include "state_machine.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	bitSearchingFSM(TIMEOUT_EVT);
}
