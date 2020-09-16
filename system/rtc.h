/*
 * rtc.h
 *
 * Created: 2020-09-15 3:43:14 PM
 *  Author: charl
 */ 


#ifndef RTC_H_
#define RTC_H_

#include "tinylibdef.h"

typedef uint32_t SysTime_t;

#ifndef SYSTIME_NONE
#define SYSTIME_NONE 0x00000000
#endif

void vRTCSetup(void);
SysTime_t xRTCGetSystemTime(void);

#endif /* RTC_H_ */