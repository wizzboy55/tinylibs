/*
 * tinylibdef.h
 *
 * Created: 2020-08-27 2:18:59 PM
 *  Author: charl
 */ 


#ifndef TINYLIBDEF_H_
#define TINYLIBDEF_H_

#include <stdint.h>
#include <stddef.h>

typedef signed char BaseType_t;
typedef unsigned char UBaseType_t;

#define pdFALSE (0)
#define pdTRUE (1)

#define DISABLE_INTERRUPTS()	asm volatile ( "cli" :: );
#define ENABLE_INTERRUPTS()		asm volatile ( "sei" :: );


#endif /* TINYLIBDEF_H_ */