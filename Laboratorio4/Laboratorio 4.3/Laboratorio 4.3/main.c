/*
 * Laboratorio 4.3.c
 *
 * Created: 11/02/2025 22:47:55
 * Author : jaidy
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "I2C/I2C_SLAVE.h"
#include "PIN_INT/Ext_Int.h"

uint8_t cont = 2;
volatile uint8_t dato_recibido;
volatile uint8_t dato_a_enviar = 0x22;


int main(void){
    I2C_esclavo_init();			// Inicializa el esclavo
	initPinChange0(rising_edge);//INTERRUPCION EXTERNA PD2 FLANCO DE BAJADA
	initPinChange1(rising_edge);//INTERRUPCION ECTERNA PD3 FLANCO DE BAJADA
    sei();						// Habilita interrupciones globales
    DDRB = 0xFF;
    while (1){
		
    }
}

ISR(TWI_vect) {
	switch (TWSR & 0xF8) {
		case 0x80:				// Dato recibido de maestro
		dato_recibido = TWDR;	// Guarda el dato recibido
		PORTB = dato_recibido;
		break;
		case 0xA8:				// Maestro solicita lectura
		TWDR = cont;			// Carga el dato a enviar
		cont = 2;
		break;
	}
	I2C_reset();				// Reinicia I2C para recibir más datos
}

ISR (INT0_vect){
	_delay_ms(100);
	cont = 1;
}

ISR (INT1_vect){
	_delay_ms(100);
	cont = 0;
}