/*
 * rtc.c
 *
 * Created: 2020-09-15 3:43:03 PM
 *  Author: charl
 */ 

#include "rtc.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include "osconfig.h"

SysTime_t xSystemTime = 0;

inline void vRTCSetup(void) {
	CLKCTRL.OSC32KCTRLA = CLKCTRL_RUNSTDBY_bm;
	RTC.CLKSEL = RTC_CLKSEL_INT32K_gc;  // May be modified by Sleep functions
	// System Tick Timer
	#if OS_FREQUENCY == 1024
	RTC.PITCTRLA  = RTC_PERIOD_CYC32_gc | RTC_PITEN_bm;
	RTC.PITINTCTRL = RTC_PI_bm;
	#elif OS_FREQUENCY == 512
	RTC.PITCTRLA  = RTC_PERIOD_CYC64_gc | RTC_PITEN_bm;
	RTC.PITINTCTRL = RTC_PI_bm;
	#elif OS_FREQUENCY == 256
	RTC.PITCTRLA  = RTC_PERIOD_CYC128_gc | RTC_PITEN_bm;
	RTC.PITINTCTRL = RTC_PI_bm;
	#elif OS_FREQUENCY == 128
	RTC.PITCTRLA  = RTC_PERIOD_CYC256_gc | RTC_PITEN_bm;
	RTC.PITINTCTRL = RTC_PI_bm;
	#elif OS_FREQUENCY == 64
	RTC.PITCTRLA  = RTC_PERIOD_CYC512_gc | RTC_PITEN_bm;
	RTC.PITINTCTRL = RTC_PI_bm;
	#elif OS_FREQUENCY == 32
	RTC.PITCTRLA  = RTC_PERIOD_CYC1024_gc | RTC_PITEN_bm;
	RTC.PITINTCTRL = RTC_PI_bm;
	#elif OS_FREQUENCY == 0
	
	#else
	#error osconfig.h Invalid OS_FREQUENCY value using RTC!
	#endif
	// System Time Interrupt
	RTC.INTCTRL = RTC_OVF_bm;
	RTC.PER = 0x8000;
	RTC.CMP = 0x8000;
	
	#ifdef DEBUG
	RTC.DBGCTRL |= RTC_DBGRUN_bm;
	RTC.PITDBGCTRL |= RTC_DBGRUN_bm;
	#endif
	
	RTC.CTRLA = RTC_RTCEN_bm | RTC_PRESCALER_DIV1_gc | RTC_RUNSTDBY_bm;
}

inline SysTime_t xRTCGetSystemTime(void) {
	return xSystemTime;
}

ISR( RTC_CNT_vect ) {
	RTC.INTFLAGS = RTC_OVF_bm | RTC_CMP_bm;
	xSystemTime++;
}

#if OS_FREQUENCY != 0
ISR( RTC_PIT_vect ) {
	RTC.PITINTFLAGS = RTC_PI_bm;
}
#endif