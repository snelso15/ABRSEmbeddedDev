/*
 * PiSPICommands.h
 *
 *  Created on: Jan 28, 2016
 *      Author: new
 */

#ifndef PISOURCES_PISPICOMMANDS_H_
#define PISOURCES_PISPICOMMANDS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <wiringPiSPI.h>
#include "CANConstants.h"
#include "utils.h"

int initSPI();
uint8_t readReg(uint8_t regAddress);
void writeReg(uint8_t regAddress, uint8_t val);
void bitModReg(uint8_t regAddress, uint8_t mask, uint8_t byteToWrite);
void resetCAN();

#ifdef __cplusplus
}
#endif

#endif /* PISOURCES_PISPICOMMANDS_H_ */
