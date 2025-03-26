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

void initPinChange1(uint8_t edge) {
	// Configurar PC0-PC5 como entradas
	DDRC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5));

	if (edge == 1) {
		// Deshabilitar pull-up en PC0-PC5
		PORTC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5));
		} else {
		// Habilitar pull-up en PC0-PC5
		PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5);
	}

	// Habilitar interrupción por cambio de pines en PC0-PC5
	PCICR |= (1 << PCIE1); // Habilita interrupciones en el grupo PCINT8-14 (puerto C)
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11) | (1 << PCINT12) | (1 << PCINT13);
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
