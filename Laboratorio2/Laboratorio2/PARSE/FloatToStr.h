/*
 * FloatToStr.h
 *
 * Created: 3/02/2025 23:45:52
 *  Author: jaidy
 */ 


#ifndef FLOATTOSTR_H_
#define FLOATTOSTR_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void float_to_string(float num, char *buffer, int precision);

#endif /* FLOATTOSTR_H_ */