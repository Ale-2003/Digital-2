/*
 * Proyecto1.2.c
 *
 * Created: 25/02/2025 21:23:20
 * Author : jaidy
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "I2C/I2C_SLAVE.h"
#include "DHT11/DHT11.h"

uint8_t temperatura = 1;
volatile uint8_t dato_recibido;
volatile uint8_t dato_a_enviar = 0x22;


int main(void){
	I2C_esclavo_init();			// Inicializa el esclavo
	sei();						// Habilita interrupciones globales
	while (1){
		temperatura = Read_TempInt();
	}
}

ISR(TWI_vect) {
	switch (TWSR & 0xF8) {
		case 0x80:				// Dato recibido de maestro
		dato_recibido = TWDR;	// Guarda el dato recibido
		PORTB = dato_recibido;
		break;
		case 0xA8:				// Maestro solicita lectura
		TWDR = temperatura;			// Carga el dato a enviar
		break;
	}
	I2C_reset();				// Reinicia I2C para recibir más datos
}