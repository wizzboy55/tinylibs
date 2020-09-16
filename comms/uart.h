/*
 * uart.h
 *
 * Created: 2020-09-01 10:04:13 AM
 *  Author: charl
 */ 


#ifndef UART_H_
#define UART_H_

#include "gpio.h"

#define UART_BAUDRATE(BAUD_RATE) ((float)(CPU_FREQUENCY * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#ifdef TINYx14
	#define UART_PORT_RX_ALT	GPIO_PORTA
	#define UART_PIN_RX_ALT		2
	#define UART_PORT_TX_ALT	GPIO_PORTA
	#define UART_PIN_TX_ALT		1
	#define UART_PORT_RX		GPIO_PORTB
	#define UART_PIN_RX			3
	#define UART_PORT_TX		GPIO_PORTB
	#define UART_PIN_TX			2
#else
	#error UART: Unsupported MCU!
#endif 

#endif /* UART_H_ */