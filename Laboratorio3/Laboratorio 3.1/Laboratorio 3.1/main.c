//********************************************************************************
/* Universidad del Valle de Guatemala
 * IE3054: Electronica digital 2
 * Autor: Alejandra Marcos y Luis Furlan
 * Laboratorio 3.1.c
 *
 * Created: 6/02/2025 16:50:16
 * Author : jaidy
 */ 

//LIBRERIAS
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SPI/SPI_SLAVE.h"
#include "ADC/ADC.h"

//VARIABLES
uint8_t received_data = 0;
uint8_t flag = 0;
uint8_t last_data = 0;

//FUNCIONES

int main(void){
	SPI_SlaveInit();		// INICIALIZA EL SPI
	initADC();				// INICIALIZA EL ADC
	UCSR0B = 0;				// DESACTIVA RX Y TX
	sei();					// ACTIVA LAS INTERRUPCIONES
	DDRD = 0xFF;			// PUERTO D COMO SALIDA
	
    while (1) {
	
    }
}

ISR(SPI_STC_vect) {
	received_data = SPDR;   // CAPTURA EL DATO RECIBIDO
	switch (received_data){
		case 'A': SPDR = ADC_CONVERT(0); break;
		case 'B': SPDR = ADC_CONVERT(1); break;
		case '0': PORTD = '0'; break;
		case '1': PORTD = '1'; break;
		case '2': PORTD = '2'; break;
		case '3': PORTD = '3'; break;
		case '4': PORTD = '4'; break;
		case '5': PORTD = '5'; break;
		case '6': PORTD = '6'; break;
		case '7': PORTD = '7'; break;
		case '8': PORTD = '8'; break;
		case '9': PORTD = '9'; break;
		case 'C': PORTD = 'C'; break;
		case 'D': PORTD = 'D'; break;
		case 'E': PORTD = 'E'; break;
		case 'F': PORTD = 'F'; break;
		case 'G': PORTD = 'G'; break;
		case 'H': PORTD = 'H'; break;
		case 'I': PORTD = 'I'; break;
		case 'J': PORTD = 'J'; break;
		case 'K': PORTD = 'K'; break;
		case 'L': PORTD = 'L'; break;
		case 'M': PORTD = 'M'; break;
		case 'N': PORTD = 'N'; break;
		case 'O': PORTD = 'O'; break;
		case 'P': PORTD = 'P'; break;
		case 'Q': PORTD = 'Q'; break;
		case 'R': PORTD = 'R'; break;
		case 'S': PORTD = 'S'; break;
		case 'T': PORTD = 'T'; break;
		case 'U': PORTD = 'U'; break;
		case 'V': PORTD = 'V'; break;
		case 'W': PORTD = 'W'; break;
		case 'X': PORTD = 'X'; break;
		case 'Y': PORTD = 'Y'; break;
		case 'Z': PORTD = 'Z'; break;
		case 'a': PORTD = 'a'; break;
		case 'b': PORTD = 'b'; break;
		case 'c': PORTD = 'c'; break;
		case 'd': PORTD = 'd'; break;
		case 'e': PORTD = 'e'; break;
		case 'f': PORTD = 'f'; break;
		case 'g': PORTD = 'g'; break;
		case 'h': PORTD = 'h'; break;
		case 'i': PORTD = 'i'; break;
		case 'j': PORTD = 'j'; break;
		case 'k': PORTD = 'k'; break;
		case 'l': PORTD = 'l'; break;
		case 'm': PORTD = 'm'; break;
		case 'n': PORTD = 'n'; break;
		case 'o': PORTD = 'o'; break;
		case 'p': PORTD = 'p'; break;
		case 'q': PORTD = 'q'; break;
		case 'r': PORTD = 'r'; break;
		case 's': PORTD = 's'; break;
		case 't': PORTD = 't'; break;
		case 'u': PORTD = 'u'; break;
		case 'v': PORTD = 'v'; break;
		case 'w': PORTD = 'w'; break;
		case 'x': PORTD = 'x'; break;
		case 'y': PORTD = 'y'; break;
		case 'z': PORTD = 'z'; break;
		case 0x20: PORTD = ' '; break;
		case 0x21: PORTD = '!'; break;
		case 0x22: PORTD = '"'; break;
		case 0x23: PORTD = '#'; break;
		case 0x24: PORTD = '$'; break;
		case 0x25: PORTD = '%'; break;
		case 0x26: PORTD = '&'; break;
		case 0x27: PORTD = '\''; break;
		case 0x28: PORTD = '('; break;
		case 0x29: PORTD = ')'; break;
		case 0x2A: PORTD = '*'; break;
		case 0x2B: PORTD = '+'; break;
		case 0x2C: PORTD = ','; break;
		case 0x2D: PORTD = '-'; break;
		case 0x2E: PORTD = '.'; break;
		case 0x2F: PORTD = '/'; break;
		default: SPDR = 0x11; break;
	}
}