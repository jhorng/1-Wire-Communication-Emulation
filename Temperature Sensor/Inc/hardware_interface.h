/*
 * function.h
 *
 *  Created on: Jul 3, 2017
 *      Author: Jaan Horng
 */

#ifndef HARDWARE_INTERFACE_H
#define HARDWARE_INTERFACE_H

#define BYTE0 (uint8_t)0x0
#define BYTE1 (uint8_t)0xFF

#define RECEIVE   0
#define TRANSMIT  1

void halfDuplex_EnableTxRx();
void timerStart();
void timerStop();
void owTransmit(uint8_t *pData, int dataSize);
void owReceive(uint8_t *pData, int dataSize);
void resetPulse();
void presencePulseDetect();
void searchROM();
void readROM();
void skipROM();
void readPowerSupply();
void owReadSlot();

#endif /* HARDWARE_INTERFACE_H */
