/*
 * IntExt.c
 *
 * Created: 22/01/2025 22:12:24
 *  Author: jaidy
 */ 
#include "IntExt.h"

void initPinChange0(uint8_t edge){
	if (edge == 1){
		DDRB &= ~(1 << PORTB0);		
		PORTB &=~(1 << PORTB0);
		}else{
		DDRB &= ~(1 << PORTB0);
		PORTB |= (1 << PORTB0);
	}
	PCICR |= (1 << PCIF0);
	PCMSK0 |= (1 << PCINT0);
}

void initPinChange1(uint8_t edge){
	if (edge == 1){
		DDRB &= ~(1 << PORTB1);
		PORTB &=~(1 << PORTB1);
		}else{
		DDRB &= ~(1 << PORTB1);
		PORTB |= (1 << PORTB1);
	}
	PCICR |= (1 << PCIF0);
	PCMSK0 |= (1 << PCINT1);
}

void initPinChange2(uint8_t edge){
	if (edge == 1){
		DDRB &= ~(1 << PORTB2);
		PORTB &=~(1 << PORTB2);
		}else{
		DDRB &= ~(1 << PORTB2);
		PORTB |= (1 << PORTB2);
	}
	PCICR |= (1 << PCIF0);
	PCMSK0 |= (1 << PCINT2);
}
