/*
 * Laboratorio 4.2.c
 *
 * Created: 11/02/2025 22:25:56
 * Author : jaidy
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include "I2C/I2C_SLAVE.h"
#include "ADC/ADC.h"

volatile uint8_t dato_recibido;
uint8_t dato_a_enviar = 0;


int main(void){
	I2C_esclavo_init();			// Inicializa el esclavo
	initADC();
	sei();						// Habilita interrupciones globales
	DDRD = 0xFF;
    while (1){
		dato_a_enviar = ADC_CONVERT(0);
    }
}

ISR(TWI_vect) {
	switch (TWSR & 0xF8) {
		case 0x80:				// Dato recibido de maestro
		dato_recibido = TWDR;	// Guarda el dato recibido
		PORTD = dato_recibido;
		break;
		case 0xA8:				// Maestro solicita lectura
		TWDR = dato_a_enviar;	// Carga el dato a enviar
		break;
	}
	I2C_reset();				// Reinicia I2C para recibir más datos
}