/*
 * DHT11.h
 *
 * Created: 25/02/2025 21:39:59
 *  Author: jaidy
 */ 


#ifndef DHT11_H_
#define DHT11_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DHT11_PIN  PC0  // Pin de datos conectado a PD2
uint8_t hum_int, hum_dec, temp_int, temp_dec, checksum;

void Request();

uint8_t Response();

uint8_t Read_Data();

uint8_t Read_TempInt();

#endif /* DHT11_H_ */