//********************************************************************************
/* Universidad del Valle de Guatemala
 * IE3054: Electronica digital 2
 * Autor: Alejandra Marcos
 * Laboratorio1.c
 *
 * Created: 22/01/2025 22:03:06
 * Author : jaidy
 */ 
//********************************************************************************

//LIBRERIAS
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "IntExt/IntExt.h"
#include "Display7/Display7.h"


//VARIABLES
uint8_t Jugador1 = 0;
uint8_t Jugador2 = 0;
uint8_t Ganador = 0;
uint8_t STATE = 0;
uint8_t NEXT_STATE = 0;
int numero[5] = {0,1, 2, 4, 8};
uint8_t bloqueoJ1 = 0;
uint8_t bloqueoJ2 = 0;

//FUNCIONES
void No_Jugar(void);
void Si_Jugar(void);
void Mascara(uint8_t number1, uint8_t number2);

int main(void){
	//cli();
	initPinChange0(falling_edge); // INTERRUPCION EXTERNA PB0 FLANCO DE BAJADA
	initPinChange1(falling_edge); // INTERRUPCION EXTERNA PB1 FLANCO DE BAJADA
	initPinChange2(falling_edge); // INTERRUPCION EXTERNA PB2 FLANCO DE BAJADA
	UCSR0B = 0; // DESHABILITA TX Y RX
	DDRD = 255;
	DDRC = 255;
	DDRB = 0;
	DDRB |= (1 << PORTB5);
	STATE = 0;
	sei();
    while (1){
		switch (STATE){
			case 0: No_Jugar(); NEXT_STATE = 1; break; // JUEGO NO INICIADO
			case 1: Si_Jugar(); NEXT_STATE = 0; break; // JUEGO INICIADO
			default: STATE = 0; break;
		}
    }
}

void No_Jugar(void){
	STATE = 0;
	Ganador = 0;
	Jugador1 = 0;
	Jugador2 = 0;
}

void Si_Jugar(void){
	Mascara(numero[Jugador1], numero[Jugador2]);
	if (Ganador == 2){
		Display7S(2);
		Jugador1 = 0;
	}
	if (Ganador == 1){
		Display7S(1);
		Jugador2 = 0;
	}
}

void Mascara(uint8_t number1, uint8_t number2){
	number1 &= 0x0F; // PD0-PD3
	number2 &= 0x0F; // PD4-PD7
	PORTD &= ~((0x0F) | (0xF0));
	PORTD |= number1; // ESCRIBIMOS EN PD0-PD3
	PORTD |= (number2 << 4); // ESCRIBIMOS EN PD4-PD7
}

ISR (PCINT0_vect){
	_delay_ms(100);
	if (!(PINB & (1 << PORTB0))) {
		if (STATE == 0){
			Display7S(5);
			_delay_ms(500);
			Display7S(4);
			_delay_ms(500);
			Display7S(3);
			_delay_ms(500);
			Display7S(2);
			_delay_ms(500);
			Display7S(1);
			_delay_ms(500);
			Display7S(0);
			_delay_ms(500);
			Display7S(10);
		}else{
			Jugador1 = 0;
			Jugador2 = 0;
			Ganador = 0;
		}
		STATE = NEXT_STATE;
	}
	
	if (!(PINB & (1 << PORTB1))) {
		if (STATE != 0 && bloqueoJ1 == 0){
			if (Jugador1 < 4){
				Jugador1++;
			}
			if (Jugador1 == 4){
				Ganador = 1;
			}
			bloqueoJ1 = 1;		// ACTIVAR BLOQUE0 PARA EVITAR INCREMENTO CONTINUO
		}
	} else {
		bloqueoJ1 = 0;			// RESETEAR BLOQUEO CUANDO SE SUELTA EL BOTON
	}
	
	if (!(PINB & (1 << PORTB2))) {
		if (STATE != 0 && bloqueoJ2 == 0){
			if (Jugador2 < 4){
				Jugador2++;
				if (Jugador2 == 4){
					Ganador = 2;
				}
			}
			bloqueoJ2 = 1;
		}
	} else {
		bloqueoJ2 = 0;
	}
}
