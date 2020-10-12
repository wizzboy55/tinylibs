/*
 * twi.h
 *
 * Created: 2020-10-09 2:48:38 PM
 *  Author: charl
 */ 


#ifndef TWI_H_
#define TWI_H_

#include "tinylibdef.h"

#include <avr/io.h>

enum TwiCommand_e {TWI_NoAction = 0x00, TWI_CompleteTransaction = 0x02, TWI_Response = 0x03};

#define TWI_SET_ADDRESS(x) TWI0.SADDR = x << 1;

#endif /* TWI_H_ */