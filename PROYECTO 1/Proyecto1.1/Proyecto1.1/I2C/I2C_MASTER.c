/*
 * I2C_MASTER.c
 *
 * Created: 11/02/2025 21:54:41
 *  Author: jaidy
 */ 
#include "I2C_MASTER.h"

void I2C_init() {
	TWSR = 0x00;							// CONFIGURA PRESCALER 1
	TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;  // CONFIGURA LA FRECUENCIA DE SCL
	TWCR = (1 << TWEN);						// HABILITA I2C
	//PORTC |= (1 << PC4) | (1 << PC5);		// HABILITA PULL-UPS INTERNOS EN SDA Y SCL
}

void I2C_start() {
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);	// INICIA CONDICION START
	while (!(TWCR & (1 << TWINT)));						// ESPERA A QUE SE COMPLETE
}

void I2C_stop() {
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);	// INICIA CONDICION STOP
}

void I2C_write(uint8_t data) {
	TWDR = data;							// CARGA EL DATO EN EL REGISTRO
	TWCR = (1 << TWEN) | (1 << TWINT);		// INICIA LA TRANSMISION
	while (!(TWCR & (1 << TWINT)));			// ESPERA A QUE SE COMPLETE
}

uint8_t I2C_read_ack() {
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);	// HABILITA ACK
	while (!(TWCR & (1 << TWINT)));						// ESPERA A QUE SE COMPLETE
	return TWDR;										// RETORNA EL DATO LEIDO
}

uint8_t I2C_read_nack() {
	TWCR = (1 << TWEN) | (1 << TWINT);		// NO ENVIA ACK
	while (!(TWCR & (1 << TWINT)));			// ESPERA A QUE SE COMPLETE
	return TWDR;							// RETORNA EL DATO LEIDO
}
