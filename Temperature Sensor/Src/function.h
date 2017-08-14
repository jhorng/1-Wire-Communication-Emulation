/*
 * function.h
 *
 *  Created on: Jul 3, 2017
 *      Author: Prince
 */

#ifndef FUNCTION_H
#define FUNCTION_H

#define BYTE0 (uint8_t)0x0
#define BYTE1 (uint8_t)0xFF

#define RECEIVE   0
#define TRANSMIT  1

void timerStart(TIM_HandleTypeDef *htim);
void timerStop(TIM_HandleTypeDef *htim);
void masterTransmitReceive(int txRx, uint8_t *pData, int dataSize);
void masterReadSlot();
void resetPulse();
void presencePulseDetect();
void searchROM();
void readROM();
void skipROM();
void readPowerSupply();

#endif /* FUNCTION_H */