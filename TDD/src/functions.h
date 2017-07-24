#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <stdlib.h>
#include <stdint.h>

void masterWriteByteWithInterrupt(uint8_t *byte, int dataSize);
void resetPulse();
void presencePulseDetect();
void searchROM();
void readROM();
void skipROM();
void readPowerSupply();
void HAL_HalfDuplex_EnableTxRx();
void HAL_TIM_Base_Start_IT();

#endif // _FUNCTIONS_H
