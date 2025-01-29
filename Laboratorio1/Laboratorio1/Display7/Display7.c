/*
 * Display7.c
 *
 * Created: 23/01/2025 19:06:12
 *  Author: jaidy
 */ 
#include "Display7.h"

void Display7S(uint8_t num){
	switch(num){
		case 0: PORTC = 0b1111110; PORTB |=  (1 << PORTB5); break;
		case 1: PORTC = 0b0110000; PORTB &= ~(1 << PORTB5); break;
		case 2: PORTC = 0b1101101; PORTB |=  (1 << PORTB5); break;
		case 3: PORTC = 0b1111001; PORTB |=  (1 << PORTB5); break;
		case 4: PORTC = 0b0110011; PORTB &= ~(1 << PORTB5); break;
		case 5: PORTC = 0b1011011; PORTB |=  (1 << PORTB5); break;
		case 6: PORTC = 0b1101111; PORTB |=  (1 << PORTB5); break;
		case 7: PORTC = 0b1110000; PORTB |=  (1 << PORTB5); break;
		case 8: PORTC = 0b1111111; PORTB |=  (1 << PORTB5); break;
		case 9: PORTC = 0b1111011; PORTB |=  (1 << PORTB5); break;
		default: PORTC = 0; PORTB &= ~(1 << PORTB5); break;
	}
	
}