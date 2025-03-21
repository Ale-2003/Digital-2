/*
 * SPI_SLAVE.h
 *
 * Created: 6/02/2025 16:57:50
 *  Author: jaidy
 */ 


#ifndef SPI_SLAVE_H_
#define SPI_SLAVE_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define DD_MISO PB4
#define DD_MOSI PB3
#define DD_SCK PB5
#define DD_SS PB2
#define DDR_SPI DDRB

void SPI_SlaveInit(void);

#endif /* SPI_SLAVE_H_ */