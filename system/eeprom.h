/*
 * eeprom.h
 *
 * Created: 2020-09-16 9:14:35 AM
 *  Author: charl
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "tinylibdef.h"

void vEEPROMInit(void);
void vEEPROMWriteBlock(uint16_t usEepromAddress, uint8_t *data, size_t size);
void vEEPROMReadBlock(uint16_t usEepromAddress, uint8_t *data, size_t size);

#endif /* EEPROM_H_ */