/*
 * SPI_SLAVE.c
 *
 * Created: 6/02/2025 17:02:05
 *  Author: jaidy
 */ 
#include "SPI_SLAVE.h"

void SPI_SlaveInit(void) {
	DDR_SPI &= ~((1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS)); // MOSI, SCK, SS COMO ENTRADA
	DDR_SPI |= (1 << DD_MISO);									 // MISO COMO SALIDA
	SPCR = (1 << SPE) | (1 << SPIE);				// HABILITA MODO ESCLAVO Y LA INTERRUPCION
	SPCR &= ~((1 << CPOL) | (1 << CPHA));			// SPI MODO 0 (CPOL=0, CPHA=0)
}
