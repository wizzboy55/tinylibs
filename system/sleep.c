/*
 * sleep.c
 *
 * Created: 2020-08-26 6:51:01 PM
 *  Author: charl
 */ 

#include "sleep.h"

#include <avr/io.h>

inline void vTinySleepIdle(void) {
	SLPCTRL.CTRLA = SLPCTRL_SEN_bm | SLPCTRL_SMODE_IDLE_gc;
	
	#ifndef DEBUG
		asm volatile (
		"    sleep\n"
		);
	#endif
}

inline void vTinySleepStandBy(void) {
	SLPCTRL.CTRLA = SLPCTRL_SEN_bm | SLPCTRL_SMODE_STDBY_gc;
	
	#ifndef DEBUG
		asm volatile (
		"    sleep\n"
		);
	#endif
}

inline void vTinySleepPowerDown(void) {
	SLPCTRL.CTRLA = SLPCTRL_SEN_bm | SLPCTRL_SMODE_PDOWN_gc;
	
	#ifndef DEBUG
		asm volatile (
		"    sleep\n"
		);
	#endif
}