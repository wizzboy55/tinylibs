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

#define TINYWATCHDOG_ENABLE(frequency) \
	CCP_UNLOCK_IO_REGISTERS(); \
	WDT.CTRLA = WDT_WINDOW_OFF_gc | frequency;

#define TINYWATCHDOG_DISABLE() \
	CCP_UNLOCK_IO_REGISTERS(); \
	WDT.CTRLA = WDT_WINDOW_OFF_gc | WDT_PERIOD_OFF_gc;

#define TINYWATCHDOG_RESET()	\
	asm volatile (			\
	"    wdr"	"\n"		\
	);					

#endif /* WDT_H_ */