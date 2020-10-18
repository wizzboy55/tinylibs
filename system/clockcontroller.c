/*
 * clockcontroller.c
 *
 * Created: 2020-08-26 4:10:54 PM
 *  Author: charl
 */ 

#include "clockcontroller.h"
#include "ccp.h"

#include <avr/io.h>

inline void vTinyMainClockSetup(const MCLKDivider_t divider) {
//	CCP_UNLOCK_IO_REGISTERS();
//	CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSC20M_gc; // OSC20M by default
	ccp_write_io((void*)&CLKCTRL.MCLKCTRLB, (uint8_t)divider);
	ccp_write_io((void*)&CLKCTRL.MCLKLOCK, CLKCTRL_LOCKEN_bm);
} 

inline void vTinySetup32kULP(void) {
	CLKCTRL.OSC32KCTRLA = CLKCTRL_RUNSTDBY_bm;
}