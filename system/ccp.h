/*
 * ccp.h
 *
 * Created: 2020-08-26 6:29:31 PM
 *  Author: charl
 */ 


#ifndef CCP_H_
#define CCP_H_

#include <avr/io.h>

#define CCP_UNLOCK_IO_REGISTERS()		CCP = 0xD8
#define CCP_UNLOCK_SPM_REGISTERS()		CCP = 0x9D

#endif /* CCP_H_ */