/******************************************************************************

    @file    IntrOS: osport.c
    @author  Rajmund Szymanski
    @date    29.03.2020
    @brief   IntrOS port file for ATtiny817 uC.

 ******************************************************************************

   Copyright (c) 2018-2020 Rajmund Szymanski. All rights reserved.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to
   deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
   sell copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
   IN THE SOFTWARE.

 ******************************************************************************/

#include "oskernel.h"

/* -------------------------------------------------------------------------- */

void port_sys_init( void )
{
#ifdef OS_USE_RTC
	
	CLKCTRL.OSC32KCTRLA = CLKCTRL_RUNSTDBY_bm;
	//	RTC.CLKSEL = RTC_CLKSEL_INT32K_gc; // ULP32K by default
	// System Tick Timer
	#if OS_FREQUENCY == 1024
		RTC.PITCTRLA  = RTC_PERIOD_CYC32_gc | RTC_PITEN_bm;
	#elif OS_FREQUENCY == 512
		RTC.PITCTRLA  = RTC_PERIOD_CYC64_gc | RTC_PITEN_bm;
	#elif OS_FREQUENCY == 256
		RTC.PITCTRLA  = RTC_PERIOD_CYC128_gc | RTC_PITEN_bm;
	#elif OS_FREQUENCY == 128
		RTC.PITCTRLA  = RTC_PERIOD_CYC256_gc | RTC_PITEN_bm;
	#elif OS_FREQUENCY == 64
		RTC.PITCTRLA  = RTC_PERIOD_CYC512_gc | RTC_PITEN_bm;
	#elif OS_FREQUENCY == 32
		RTC.PITCTRLA  = RTC_PERIOD_CYC1024_gc | RTC_PITEN_bm;
	#else
		#error osconfig.h Invalid OS_FREQUENCY value using RTC!
	#endif
	RTC.PITINTCTRL = RTC_PI_bm;
	// System Time Interrupt
	RTC.INTCTRL = RTC_OVF_bm;
	RTC.PER = 0x8000;
	RTC.CTRLA = RTC_RTCEN_bm | RTC_PRESCALER_DIV1_gc | RTC_RUNSTDBY_bm;
	
#elif HW_TIMER_SIZE == 0

/******************************************************************************
 Non-tick-less mode: configuration of system timer
 It must generate interrupts with frequency OS_FREQUENCY
*******************************************************************************/

	TCA0.SINGLE.PER     = (CPU_FREQUENCY)/(OS_FREQUENCY)/16-1;
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	TCA0.SINGLE.CTRLB   = TCA_SINGLE_WGMODE_NORMAL_gc;
	TCA0.SINGLE.CTRLA   = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV16_gc;

/******************************************************************************
 End of configuration
*******************************************************************************/

#else //HW_TIMER_SIZE

/******************************************************************************
 Tick-less mode: configuration of system timer
 It must be rescaled to frequency OS_FREQUENCY
*******************************************************************************/

	TCA0.SINGLE.PER     = UINT16_MAX;
	#if HW_TIMER_SIZE < OS_TIMER_SIZE
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	#endif
	TCA0.SINGLE.CTRLB   = TCA_SINGLE_WGMODE_NORMAL_gc;
	#if   CPU_FREQUENCY == (OS_FREQUENCY) * 1
	TCA0.SINGLE.CTRLA   = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV1_gc;
	#elif CPU_FREQUENCY == (OS_FREQUENCY) * 2
	TCA0.SINGLE.CTRLA   = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV2_gc;
	#elif CPU_FREQUENCY == (OS_FREQUENCY) * 4
	TCA0.SINGLE.CTRLA   = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV4_gc;
	#elif CPU_FREQUENCY == (OS_FREQUENCY) * 8
	TCA0.SINGLE.CTRLA   = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV8_gc;
	#elif CPU_FREQUENCY == (OS_FREQUENCY) * 16
	TCA0.SINGLE.CTRLA   = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV16_gc;
	#elif CPU_FREQUENCY == (OS_FREQUENCY) * 64
	TCA0.SINGLE.CTRLA   = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV64_gc;
	#elif CPU_FREQUENCY == (OS_FREQUENCY) * 256
	TCA0.SINGLE.CTRLA   = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV256_gc;
	#elif CPU_FREQUENCY == (OS_FREQUENCY) * 1024
	TCA0.SINGLE.CTRLA   = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV1024_gc;
	#else
	#error osconfig.h: Invalid OS_FREQUENCY value!
	#endif

/******************************************************************************
 End of configuration
*******************************************************************************/

#endif//HW_TIMER_SIZE

	port_clr_lock();
}

/* -------------------------------------------------------------------------- */

volatile SysTime_t xSystemTime = 0;

inline SysTime_t xPortGetSystemTime(void) {
	return xSystemTime;
}

#ifdef OS_USE_RTC

// System Tick Interrupt (OS_FREQUENCY)
ISR( RTC_PIT_vect ) {
	RTC.PITINTFLAGS = RTC_PI_bm;
	core_sys_tick();
}

// System Time Interrupt (every second)
ISR( RTC_CNT_vect ) {
	RTC.INTFLAGS = RTC_OVF_bm | RTC_CMP_bm;
	xSystemTime++;
}

#elif HW_TIMER_SIZE == 0 && !defined(OS_USE_RTC)

/******************************************************************************
 Non-tick-less mode: interrupt handler of system timer
*******************************************************************************/

ISR( TCA0_OVF_vect )
{
//	if (TCA0.SINGLE.INTFLAGS & TCA_SINGLE_OVF_bm)
	{
		TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
		core_sys_tick();
	}
}

/******************************************************************************
 End of the handler
*******************************************************************************/

#else //HW_TIMER_SIZE

/******************************************************************************
 Tick-less mode: interrupt handler of system timer
*******************************************************************************/

#if HW_TIMER_SIZE < OS_TIMER_SIZE && !defined(OS_USE_RTC)

ISR( TCA0_OVF_vect )
{
//	if (TCA0.SINGLE.INTFLAGS & TCA_SINGLE_OVF_bm)
	{
		TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
		core_sys_tick();
	}
}

#endif

/******************************************************************************
 End of the handler
*******************************************************************************/

/******************************************************************************
 Tick-less mode: return current system time
*******************************************************************************/

#if HW_TIMER_SIZE < OS_TIMER_SIZE

cnt_t port_sys_time( void )
{
	cnt_t    cnt;
	uint16_t tck;

	cnt = System.cnt;
	tck = TCA0.SINGLE.CNT;

	if (TCA0.SINGLE.INTFLAGS & TCA_SINGLE_OVF_bm)
	{
		tck = TCA0.SINGLE.CNT;
		cnt += (cnt_t)(1) << (HW_TIMER_SIZE);
	}

	return cnt + tck;
}

#endif

/******************************************************************************
 End of the function
*******************************************************************************/

#endif//HW_TIMER_SIZE

/* -------------------------------------------------------------------------- */
