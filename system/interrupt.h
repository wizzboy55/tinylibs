/*
 * interrupt.h
 *
 * Created: 2020-08-26 6:57:23 PM
 *  Author: charl
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "tinylibdef.h"

#define INTERRUPT_ENABLE_ROUNDROBIN()		CPUINT.CTRLA |= CPUINT_LVL0RR_bm;

#endif /* INTERRUPT_H_ */