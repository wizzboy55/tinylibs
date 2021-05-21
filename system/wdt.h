/*
 * wdt.h
 *
 * Created: 2020-08-26 6:46:13 PM
 *  Author: charl
 */ 


#ifndef WDT_H_
#define WDT_H_

#include "ccp.h"
#include <avr/io.h>

#define TINYWATCHDOG_ENABLE(frequency)		ccp_write_io((void *)&(WDT.CTRLA), frequency | WDT_WINDOW_OFF_gc)

#define TINYWATCHDOG_WAITFORSYNC()			while(WDT.STATUS & WDT_SYNCBUSY_bm) {}

#define TINYWATCHDOG_DISABLE()	do {			\
	TINYWATCHDOG_WAITFORSYNC()					\
	TINYWATCHDOG_ENABLE(WDT_PERIOD_OFF_gc);		\
	TINYWATCHDOG_WAITFORSYNC()					\
} while(0)

#define TINYWATCHDOG_RESET()				asm volatile ("    wdr"	"\n")					

#endif /* WDT_H_ */