/*
 * delay.h
 *
 * Created: 2020-08-31 4:40:07 PM
 *  Author: charl
 */ 


#ifndef DELAY_H_
#define DELAY_H_

#include "tinylibdef.h"

#define DELAY_US(x)														\
for(uint8_t c = 0; c < ((x * (CPU_FREQUENCY / 1000000)) / 6); c++) {	\
	asm volatile( "nop" );												\
}																		\


#endif /* DELAY_H_ */