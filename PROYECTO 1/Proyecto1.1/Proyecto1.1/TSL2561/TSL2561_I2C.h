/*
 * TSL2561_I2C.h
 *
 * Created: 27/02/2025 18:45:49
 *  Author: jaidy
 */ 


#ifndef TSL2561_I2C_H_
#define TSL2561_I2C_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define TSL2561_ADDR 0x39
#define TSL2561_COMMAND 0x80
#define TSL2561_CONTROL 0x00
#define TSL2561_TIMING 0x01
#define TSL2561_DATA0LOW 0x0C
#define TSL2561_DATA0HIGH 0x0D

void tsl2561_init();

uint16_t tsl2561_read_luminosity();

#endif /* TSL2561_I2C_H_ */