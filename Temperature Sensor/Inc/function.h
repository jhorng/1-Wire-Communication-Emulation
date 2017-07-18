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

void masterWriteByteWithInterrupt(uint8_t *byte, int dataSize);
void resetPulse();
void presencePulseDetect();
void searchROM();
void readROM();
void skipROM();
void readPowerSupply();

#endif /* FUNCTION_H */
