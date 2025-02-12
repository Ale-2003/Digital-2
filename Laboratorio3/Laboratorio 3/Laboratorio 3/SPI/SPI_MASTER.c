/*
 * SPI_MASTER.c
 *
 * Created: 6/02/2025 16:16:14
 *  Author: jaidy
 */ 
#include "SPI_MASTER.h"

void SPI_MasterInit(void) {
	DDR_SPI |= (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);	// MOSI, SCK, SS COMO SALIDA
	DDR_SPI &= ~(1 << DD_MISO);									// MISO COMO ENTRADA
	PORTB |= (1 << DD_SS);										// DESELECCIONA AL ESCLAVO

	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);				// HABILITA EL MODO MAESTRO FCK/16
}

void SPI_MasterTransmit(uint8_t data) {
	PORTB &= ~(1 << DD_SS);										// SELECCIONA AL ESCLAVO
	SPDR = data;												// CARGA EL DATO A TRANSMITIR
	while (!(SPSR & (1 << SPIF)));								// ESPERA A QUE TERMINE LA TRANSMISION
}

uint8_t SPI_MasterReceive(void) {
	_delay_ms(1);
	SPDR = 0x00;												// ENVIAR DUMMY BITE PARA RECIBIR EL DATO
	while (!(SPSR & (1 << SPIF)));								// ESPERA HASTA RECIBIR EL DATO
	return SPDR;												// DEVUELVE EL DATO RECIBIDO
}
