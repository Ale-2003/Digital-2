/*
 * UART.c
 *
 * Created: 30/01/2025 19:29:41
 *  Author: jaidy
 */ 
#include "UART.h"

void initUART(uint8_t Fast, uint32_t BaudRate){
	// CONFIGURAR RX Y TX
	DDRD &= ~(1 << DDD0);  // RX como entrada
	DDRD |= (1 << DDD1);   // TX como salida
	
	if (Fast) {
		// CONFIGURAR EL REGISTRO A (MODO FAST U2X0 = 1)
		UCSR0A |= (1 << U2X0);
	} else {
		UCSR0A &= ~(1 << U2X0);
	}

	// CONFIGURAR BAUDRATE
	switch (BaudRate) {
		case 9600:
			UBRR0 = (Fast) ? 207 : 103;
			break;
		case 115200:
			UBRR0 = (Fast) ? 16 : 8;
			break;
		default:
			UBRR0 = 103;  // Valor por defecto: 9600 sin U2X0
			break;
	}
	
	// CONFIGURAR EL REGISTRO B (HABILITAR ISR RX, HABILITAR RX Y TX)
	UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);

	// CONFIGURAR FRAME (8 BITS DE DATO, NO PARIDAD, 1 BIT STOP)
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void write_UART(char caracter) {
	while (!(UCSR0A & (1 << UDRE0))); // Esperar a que el buffer esté vacío
	UDR0 = caracter;
}

void txt_write_UART(char* cadena) { // Enviar una cadena de caracteres
	while (*cadena != 0x00) {
		write_UART(*cadena);
		cadena++; // Incrementa la posición en la cadena
	}
}

unsigned char read_UART(void) {
	if (UCSR0A & (1 << RXC0)) { // Verificar si hay datos disponibles
		return UDR0;
	} else {
		return 0;  // Retorna 0 si no hay datos disponibles
	}
}
