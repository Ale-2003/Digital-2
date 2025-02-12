/*
 * ADC.h
 *
 * Created: 6/02/2025 18:27:44
 *  Author: jaidy
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <stdint.h>

void initADC(void);

uint16_t ADC_CONVERT(uint8_t canal);

#endif /* ADC_H_ */