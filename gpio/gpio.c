/*
 * gpio.c
 *
 * Created: 2020-08-26 9:33:20 PM
 *  Author: charl
 */ 

#include "gpio.h"

#include <stddef.h>

void vGpioSetupOutput(const ePort_t port, const uint8_t pin) {
	switch(port) {
		#ifdef PORTA
		case ePortA:
			PORTA.DIRSET = (1 << pin);
			break;
		#endif
		#ifdef PORTB
		case ePortB:
			PORTB.DIRSET = (1 << pin);
			break;
		#endif
		#ifdef PORTC
		case ePortC:
			PORTC.DIRSET = (1 << pin);
			break;
		#endif
		default:
			return;
	}
}

void vGpioSetupInput(const ePort_t port, const uint8_t pin, const BaseType_t inverted, BaseType_t pullup, const PORT_ISC_t portConfig) {
	uint8_t* pPortInputConfigReg = NULL;
	switch(port) {
	#ifdef PORTA
		case ePortA:
			PORTA.DIRCLR = (1 << pin);
			pPortInputConfigReg = (uint8_t*) &PORTA_PIN0CTRL;
			break;
	#endif
	#ifdef PORTB
		case ePortB:
			PORTB.DIRCLR = (1 << pin);
			pPortInputConfigReg = (uint8_t*) &PORTB_PIN0CTRL;
			break;
	#endif
	#ifdef PORTC
		case ePortC:
			PORTC.DIRCLR = (1 << pin);
			pPortInputConfigReg = (uint8_t*) &PORTC_PIN0CTRL;
			break;
	#endif
		default:
			return;
	}
	if(pin >= 8) {
		return;
	}
	
	pPortInputConfigReg += pin;
	
	*pPortInputConfigReg = ((inverted == pdTRUE) << PORT_INVEN_bp) | ((pullup == pdTRUE) << PORT_PULLUPEN_bp) | (portConfig & PORT_ISC_gm);
}