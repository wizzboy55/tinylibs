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

#ifdef PORTA
void vGpioPortASetPin(const uint8_t pin);
void vGpioPortAClearPin(const uint8_t pin);
void vGpioPortASetupOutput(const uint8_t pin);
void vGpioPortASetupInput(const uint8_t pin);
BaseType_t xGpioPortAReadPin(const uint8_t pin);
#endif

#ifdef PORTB
void vGpioPortBSetPin(const uint8_t pin);
void vGpioPortBClearPin(const uint8_t pin);
void vGpioPortBSetupOutput(const uint8_t pin);
void vGpioPortBSetupInput(const uint8_t pin);
BaseType_t xGpioPortBReadPin(const uint8_t pin);
#endif

void vGpioSetupInput(const ePort_t port, const uint8_t pin, const BaseType_t inverted, BaseType_t pullup, const PORT_ISC_t portConfig);
void vGpioSetupOutput(const ePort_t port, const uint8_t pin);

#endif /* GPIO_H_ */