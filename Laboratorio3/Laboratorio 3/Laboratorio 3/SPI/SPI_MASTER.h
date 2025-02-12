/*
 * SPI_MASTER.h
 *
 * Created: 6/02/2025 16:14:16
 *  Author: jaidy y luis
 */ 


#ifndef SPI_MASTER_H_
#define SPI_MASTER_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define DD_MOSI PB3
#define DD_MISO PB4
#define DD_SCK PB5
#define DD_SS PB2
#define DDR_SPI DDRB

void SPI_MasterInit(void);

void SPI_MasterTransmit(uint8_t data);

uint8_t SPI_MasterReceive(void);

#endif /* SPI_MASTER_H_ */
