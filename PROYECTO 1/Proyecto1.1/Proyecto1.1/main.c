/*
 * Proyecto1.1.c
 *
 * Created: 25/02/2025 20:49:31
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
#include "TSL2561/TSL2561_I2C.h"
#include "UART/UART.h"

uint8_t cont = 0;
uint8_t temperatura = 0;
uint8_t aire = 0;
char buffer[10];
char buffer1[5];
char buffer2[10];

int main(void){
	lcd_init();		// INICIALIZA LCD
	I2C_init();		// INICIALIZA I2C
	tsl2561_init(); // INICIALIZA SENSOR I2C
	initUART(1, 115200);
	//DDRB = 0xFF;
	DDRC |= (1 << PORTC0);
	//PORTB = 0;
	//UCSR0B = 0;
	lcd_set_cursor(0,0);
	lcd_print("Temp: Aire: Luz:");
	lcd_set_cursor(1,0);
	lcd_print("                ");
	while (1) {
		lcd_print("                ");
		lcd_set_cursor(1,2);
		lcd_print("°C");
		lcd_set_cursor(1,9);
		lcd_print("%");
		// LECTURA DEL ESCLAVO 1
		I2C_start();								// INICIA COMUNICACION I2C
		I2C_write((SLA_ESCLAVO1 << 1) | 1);			// DIRECCION DEL ESCLAVO CON BIT DE LECTURA
		uint8_t received_data = I2C_read_nack();	// LEE DATO
		I2C_stop();									// TERMINA COMUNICACION I2C
		temperatura = received_data;
		sprintf(buffer, "%d", temperatura);		//CONVIERTE A STRING
		lcd_set_cursor(1,0);
		lcd_print(buffer);
		
		// LECTURA DEL ESCLAVO 2
		I2C_start();								// INICIA COMUNICACION I2C
		I2C_write((SLA_ESCLAVO2 << 1) | 1);			// DIRECCION DEL ESCLAVO CON BIT DE LECTURA
		uint8_t received_data1 = I2C_read_nack();	// LEE DATO
		I2C_stop();									// TERMINA COMUNICACION I2C
		aire = (received_data1/225.00)*100.00;
		sprintf(buffer1, "%d", aire);				//CONVIERTE A STRING
		//lcd_set_cursor(1,6);
		//lcd_print("   %");
		lcd_set_cursor(1,6);
		lcd_print(buffer1);
		
		// ESCRITURA A ESCLAVO 3
		uint16_t luz = tsl2561_read_luminosity();	//LEE EL VALOR DEL SENSOR I2C
		if (luz <= 100) {
			PORTC |= (1 << PORTC0);					// ENCIENDE LA LUZ SI ESTA OSCURO
			} else {
			PORTC &= ~(1 << PORTC0);				// APAGA LA LUZ SI ESTA CLARO
		}
		sprintf(buffer2, "%d", luz);			    //CONVIERTE A STRING
		//lcd_set_cursor(1,12);
		//lcd_print("    ");
		lcd_set_cursor(1,12);
		lcd_print(buffer2);
		
		
		txt_write_UART("T");
		txt_write_UART(buffer);
		txt_write_UART(" A");
		txt_write_UART(buffer1);
		txt_write_UART(" L");
		txt_write_UART(buffer2);
		txt_write_UART("\n");
		_delay_ms(50);
	}
}
