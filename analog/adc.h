/*
 * adc.h
 *
 * Created: 2020-08-31 4:26:37 PM
 *  Author: charl
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "tinylibdef.h"
#include <avr/io.h>

#define ADC_START_CONVERSION(x)		do {		\
	x.INTFLAGS = ADC_RESRDY_bm;					\
	x.COMMAND = ADC_STCONV_bm;					\
} while(0);										\

#define ADC_CONVERSION_DONE(x)		(x.INTFLAGS & ADC_RESRDY_bm)

#define ADC_GET_RESULT(x)			x.RES

#endif /* ADC_H_ */