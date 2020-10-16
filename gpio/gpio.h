/*
 * gpio.h
 *
 * Created: 2020-08-26 9:33:27 PM
 *  Author: charl
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>
#include "tinylibdef.h"

typedef enum {ePortA, ePortB, ePortC} ePort_t;

#define GPIO_PORTA	0
#define GPIO_PORTB	1
#define GPIO_PORTC	2

#define GPIO_SETOUTPUT(port, pin)		port.DIRSET = (1 << pin)
#define GPIO_SETPIN(port, pin)			port.OUTSET = (1 << pin)
#define GPIO_CLRPIN(port, pin)			port.OUTCLR = (1 << pin)
#define GPIO_SETOUT(port, pin)			port.DIRSET = (1 << pin)
#define GPIO_SETIN(port, pin)			port.DIRCLR = (1 << pin)
#define GPIO_TOGGLEPIN(port, pin)		port.OUTTGL = (1 << pin)
#define GPIO_READPIN(port, pin)			((port.IN & (1 << pin)) != 0)

#define GPIO_GETPINCTRL(pin)		PIN ## pin ## CTRL

#define GPIO_SETUP_INPUT(port, pin, inverted, pullup, portConfig)	\
do {	\
	port.DIRCLR = (1 << pin);	\
	port.GPIO_GETPINCTRL(pin) = ((inverted == pdTRUE) << PORT_INVEN_bp) | ((pullup == pdTRUE) << PORT_PULLUPEN_bp) | (portConfig & PORT_ISC_gm);	\
} while (0)

void vGpioSetupInput(const ePort_t port, const uint8_t pin, const BaseType_t inverted, BaseType_t pullup, const PORT_ISC_t portConfig);
void vGpioSetupOutput(const ePort_t port, const uint8_t pin);

#endif /* GPIO_H_ */