/*
 * adc.c
 *
 * Created: 2020-08-31 4:26:32 PM
 *  Author: charl
 */ 

#include "adc.h"

#include <avr/io.h>

inline void vAdcStartConversion(void) {
	ADC0.INTFLAGS = ADC_RESRDY_bm;
	ADC0.COMMAND = ADC_STCONV_bm;
}

inline BaseType_t xAdcConversionDone(void) {
	return ADC0.INTFLAGS & ADC_RESRDY_bm;
}

inline uint16_t usAdcGetResult(void) {
	return ADC0.RES;
}