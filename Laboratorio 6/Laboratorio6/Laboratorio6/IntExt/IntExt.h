/*
 * IntExt.h
 *
 * Created: 22/01/2025 22:13:02
 *  Author: jaidy
 */ 


#ifndef INTEXT_H_
#define INTEXT_H_

#include <avr/io.h>
#include <stdint.h>

#define falling_edge 0
#define rising_edge 1

void initPinChange0(uint8_t edge);

void initPinChange1(uint8_t edge);

void initPinChange2(uint8_t edge);

#endif /* INTEXT_H_ */