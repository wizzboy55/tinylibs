/*
 * sleep.h
 *
 * Created: 2020-08-26 6:51:07 PM
 *  Author: charl
 */ 


#ifndef SLEEP_H_
#define SLEEP_H_

#include <avr/io.h>

#define TINYSLEEP_IDLE()											\
	do {															\
		SLPCTRL.CTRLA = SLPCTRL_SEN_bm | SLPCTRL_SMODE_IDLE_gc;		\
		asm volatile ("    sleep\n");								\
	} while(0)

#define TINYSLEEP_STANDBY()											\
	do {															\
		SLPCTRL.CTRLA = SLPCTRL_SEN_bm | SLPCTRL_SMODE_STDBY_gc;	\
		asm volatile ("    sleep\n");								\
	} while(0)

#define TINYSLEEP_POWERDOWN()										\
	do {															\
		SLPCTRL.CTRLA = SLPCTRL_SEN_bm | SLPCTRL_SMODE_PDOWN_gc;	\
		asm volatile ("    sleep\n");								\
	} while(0)

#endif /* SLEEP_H_ */