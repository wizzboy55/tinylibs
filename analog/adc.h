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

void vAdcStartConversion(void);
BaseType_t xAdcConversionDone(void);
uint16_t usAdcGetResult(void);


#endif /* ADC_H_ */