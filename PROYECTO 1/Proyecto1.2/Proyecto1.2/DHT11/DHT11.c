/*
 * DHT11.c
 *
 * Created: 25/02/2025 21:42:23
 *  Author: jaidy
 */ 
#include "DHT11.h"

void Request(){
	DDRC |= (1<<DHT11_PIN);  // Configura PC0 como salida
	PORTC &= ~(1<<DHT11_PIN); // Envía pulso bajo (inicio de comunicación)
	_delay_ms(18);            // Espera al menos 18 ms
	PORTC |= (1<<DHT11_PIN);  // Lleva el pin a alto
	_delay_us(20);
}

uint8_t Response(){
	DDRC &= ~(1<<DHT11_PIN);  // Configura PD2 como entrada
	_delay_us(20);
	
	if (!(PINC & (1<<DHT11_PIN))) {
		_delay_us(80);
		if (PINC & (1<<DHT11_PIN)) {
			_delay_us(80);
			return 1;  // El sensor ha respondido correctamente
		}
	}
	return 0;
}

uint8_t Read_Data(){
	uint8_t data = 0;
	
	for (int i = 0; i < 8; i++) {
		while (!(PINC & (1<<DHT11_PIN)));  // Espera el inicio del bit
		_delay_us(40);
		
		if (PINC & (1<<DHT11_PIN))  // Si el pulso es largo, es un '1'
		data = (data << 1) | 1;
		else
		data = (data << 1);
		
		while (PINC & (1<<DHT11_PIN));  // Espera que termine el bit
	}
	
	return data;
}

uint8_t Read_TempInt(){
	DDRB |= (1<<PB0);  // Configura un LED en PB0 para indicar funcionamiento
	PORTB &= ~(1<<PB0);
	
	Request();
	if (Response()) {
		hum_int = Read_Data();
		hum_dec = Read_Data();
		temp_int = Read_Data();
		temp_dec = Read_Data();
		checksum = Read_Data();
		
		if ((hum_int + hum_dec + temp_int + temp_dec) == checksum) {
			// Enviar datos a la UART (opcional)
			PORTB |= (1<<PORTB0);  // Enciende LED si la lectura es correcta
			//_delay_ms(1000);	
		}else{
			PORTB &= ~(1<<PB0);
		}
	}
	return temp_int;
}