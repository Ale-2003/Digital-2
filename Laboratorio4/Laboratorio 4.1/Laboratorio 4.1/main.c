/*
 * Laboratorio 4.1.c
 *
 * Created: 11/02/2025 21:41:15
 * Author : jaidy
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "LCD/LCD.h"
#include "I2C/I2C_MASTER.h"

uint8_t cont = 0;
float voltaje = 0;
char buffer[5];
char buffer1[5];

int main(void){
	lcd_init(); // INICIALIZA LCD
	I2C_init(); // INICIALIZA I2C
	DDRD = 0xFF;
	DDRB = 0xFF;
	PORTB = 0;
	UCSR0B = 0;
	lcd_set_cursor(0,0);
	lcd_print("  S1       S2");
	lcd_set_cursor(1,5);
	lcd_print("V");
	while (1) {
		/*// ESCRITURA A ESCLAVO 1
		I2C_start();					// INICIA COMUNICACION I2C
		I2C_write(SLA_ESCLAVO1 << 1);	// DIRECCION DEL ESCLAVO CON BIT DE LECTURA
		I2C_write(0x11);				// ENVIA DATO
		I2C_stop();						// TERMINA COMUNICACION I2C
		//_delay_ms(5);*/
		
		// LECTURA DEL ESCLAVO 1
		I2C_start();							// INICIA COMUNICACION I2C
		I2C_write((SLA_ESCLAVO1 << 1) | 1);		// DIRECCION DEL ESCLAVO CON BIT DE LECTURA
		uint8_t received_data = I2C_read_nack();// LEE DATO
		I2C_stop();								// TERMINA COMUNICACION I2C
		//PORTD = received_data;
		voltaje = (received_data/255.0)*5.0;
		dtostrf(voltaje, 1, 2, buffer);				//CONVIERTE A STRING
		lcd_set_cursor(1,1);
		lcd_print(buffer);
		//_delay_ms(5);
		
		// ESCRITURA A ESCLAVO 2
		I2C_start();
		I2C_write(SLA_ESCLAVO2 << 1);
		I2C_write(cont);
		I2C_stop();
		//_delay_ms(5);
		
		// LECTURA DEL ESCLAVO 2
		I2C_start();
		I2C_write((SLA_ESCLAVO2 << 1) | 1);
		uint8_t received_data1 = I2C_read_nack();
		I2C_stop();
		if (received_data1 == 1){
			if (cont == 15){
				cont = 15;
			}else{
				cont++;
			}
		}else if (received_data1 == 0){
			if (cont == 0){
				cont = 0;
			}else{
				cont--;
			}
		}
		sprintf(buffer1, "%d", cont);
		lcd_set_cursor(1,11);
		lcd_print("   ");
		lcd_set_cursor(1,11);
		lcd_print(buffer1);
		//PORTB = cont;
		//_delay_ms(5);
	}
}

