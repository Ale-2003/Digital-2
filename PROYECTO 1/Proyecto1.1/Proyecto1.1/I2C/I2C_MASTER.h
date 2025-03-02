/*
 * I2C_MASTER.h
 *
 * Created: 11/02/2025 21:54:14
 *  Author: jaidy
 */ 


#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define SCL_CLOCK 100000L	// FRECUENCIA DEL RELOJ I2C (100kHz)
#define SLA_ESCLAVO1 0x10   // DIRECCION DEL ESCLAVO 1
#define SLA_ESCLAVO2 0x20   // DIRECCION DEL ESCLAVO 2

void I2C_init();

void I2C_start();

void I2C_stop();

void I2C_write(uint8_t data);

uint8_t I2C_read_ack();

uint8_t I2C_read_nack();

#endif /* I2C_MASTER_H_ */