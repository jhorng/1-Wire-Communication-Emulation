/*
 * hardware_interface.h
 *
 *  Created on: Aug 15, 2017
 *      Author: Jaan Horng
 */

#ifndef HARDWARE_INTERFACE_H_
#define HARDWARE_INTERFACE_H_

#include <stdint.h>

#define BYTE0 (uint8_t)0x0
#define BYTE1 (uint8_t)0xFF

#define RECEIVE   0
#define TRANSMIT  1

void HAL_HalfDuplex_EnableTxRx();
void timerStart();
void timerStop();
void masterTransmitReceive(int txRx, uint8_t *pData, int dataSize);
void masterReadSlot();
void resetPulse();
void presencePulseDetect();
void searchROM();
void readROM();
void skipROM();
void readPowerSupply();

#endif /* HARDWARE_INTERFACE_H_ */
