/*
 * clockcontroller.h
 *
 * Created: 2020-08-26 4:11:02 PM
 *  Author: charl
 */ 


#ifndef CLOCKCONTROLLER_H_
#define CLOCKCONTROLLER_H_

#include "tinylibdef.h"

typedef enum {eDivider0 = 0x00, eDivider2 = 0x01, eDivider4 = 0x03, eDivider6 = 0x11, eDivider8 = 0x05, eDivider10 = 0x13, eDivider12 = 0x15, eDivider16 = 0x07, eDivider24 = 0x17, eDivider32 = 0x09, eDivider48 = 0x19, eDivider64 = 0x0B} MCLKDivider_t;

void vTinyMainClockSetup(const MCLKDivider_t divider);
void vTinySetup32kULP(void);

#endif /* CLOCKCONTROLLER_H_ */