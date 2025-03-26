/*
 * UART.h
 *
 * Created: 30/01/2025 19:28:39
 *  Author: jaidy
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdint.h>

#define fast 1
#define no_fast 0

void initUART(uint8_t Fast, uint32_t BaudRate);

void write_UART(char caracter);

void txt_write_UART(char* cadena);

unsigned char read_UART(void);

#endif /* UART_H_ */