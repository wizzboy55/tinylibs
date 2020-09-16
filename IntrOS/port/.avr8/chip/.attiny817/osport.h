/******************************************************************************

    @file    IntrOS: osport.h
    @author  Rajmund Szymanski
    @date    29.03.2020
    @brief   IntrOS port definitions for ATtiny817 uC.

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

#ifndef __INTROSPORT_H
#define __INTROSPORT_H

#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef   NOCONFIG
#include "osconfig.h"
#endif
#include "osdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------- */

#ifndef CPU_FREQUENCY
#define CPU_FREQUENCY         16000000UL
#endif

/* -------------------------------------------------------------------------- */

#ifndef OS_FREQUENCY
#define OS_FREQUENCY       250 /* Hz */
#endif

/* -------------------------------------------------------------------------- */
// !! WARNING! OS_TIMER_SIZE < HW_TIMER_SIZE may cause unexpected problems !!

#ifndef OS_TIMER_SIZE
#define OS_TIMER_SIZE        16 /* bit size of system timer counter           */
#endif

/* -------------------------------------------------------------------------- */
// !! WARNING! OS_TIMER_SIZE < HW_TIMER_SIZE may cause unexpected problems !!

#ifdef  HW_TIMER_SIZE
#error  HW_TIMER_SIZE is an internal os definition!
#elif   OS_FREQUENCY > 1000
#define HW_TIMER_SIZE        16 /* bit size of hardware timer                 */
#else
#define HW_TIMER_SIZE         0 /* os does not work in tick-less mode         */
#endif

/* -------------------------------------------------------------------------- */
// return current system time

#if HW_TIMER_SIZE >= OS_TIMER_SIZE

__STATIC_INLINE
uint16_t port_sys_time( void )
{
	return TCA0.SINGLE.CNT;
}

#endif

typedef uint32_t SysTime_t;

SysTime_t xPortGetSystemTime(void);

#define SYSTIME_NONE 0x00000000

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

/* -------------------------------------------------------------------------- */

#define OS_MS_TO_COUNT(x)	((cnt_t)((x * OS_FREQUENCY) / 1000UL))


#endif//__INTROSPORT_H
