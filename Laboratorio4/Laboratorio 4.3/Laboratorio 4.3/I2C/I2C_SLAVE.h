/*
 * I2C_SLAVE.h
 *
 * Created: 11/02/2025 22:36:40
 *  Author: jaidy
 */ 


#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define SLA_ESCLAVO 0x20 // Dirección del esclavo

void I2C_esclavo_init();

void I2C_reset();

#endif /* I2C_SLAVE_H_ */