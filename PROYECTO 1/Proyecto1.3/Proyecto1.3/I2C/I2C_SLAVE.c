/*
 * I2C_SLAVE.c
 *
 * Created: 11/02/2025 22:36:56
 *  Author: jaidy
 */ 
#include "I2C_SLAVE.h"

void I2C_esclavo_init() {
	TWAR = SLA_ESCLAVO << 1; // Configura la dirección del esclavo
	TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT) | (1 << TWIE); // Habilita I2C y la interrupción
	//PORTC |= (1 << PC4) | (1 << PC5); // Habilita pull-ups internos en SDA y SCL
}

void I2C_reset(){
	TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT) | (1 << TWIE); // Reinicia I2C para recibir más datos
}