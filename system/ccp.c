/*
 * ccp.c
 *
 * Created: 2020-08-26 6:29:37 PM
 *  Author: charl
 */ 

#include "ccp.h"

#include <avr/io.h>

 __attribute__((always_inline)) inline void vTinyCCPUnlockIoRegisters(void) {
	CCP = 0xD8;
}

 __attribute__((always_inline)) inline void vTinyCCPUnlockSPMRegisters(void) {
	 CCP = 0x9D;
 }