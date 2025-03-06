//********************************************************************************
/* Universidad del Valle de Guatemala
 * IE3054: Electronica digital 2
 * Autor: Alejandra Marcos y Luis Furlan
 * Proyecto1.c
 * Author : jaidy y luis
 */ 
 //********************************************************************************

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/interrupt.h>
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
volatile char bufferRX;
int flag = 1;
char control = 0;
char recibido = 0;


int main(void){
	lcd_init();		// INICIALIZA LCD
	I2C_init();		// INICIALIZA I2C
	tsl2561_init(); // INICIALIZA SENSOR I2C
	initUART(1, 115200);
	sei();
	DDRC |= (1 << PORTC0);
	DDRC |= (1 << PORTC1);
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
		
		if (control == 1)	{
			switch (recibido){
			case '2':
				I2C_start();							// INICIA COMUNICACION I2C
				I2C_write(SLA_ESCLAVO1 << 1);			// DIRECCION DEL ESCLAVO CON BIT DE LECTURA
				I2C_write('Z');						// ENVIA DATO
				I2C_stop();								// TERMINA COMUNICACION I2C
			break;
				
			case '3':
				I2C_start();							// INICIA COMUNICACION I2C
				I2C_write(SLA_ESCLAVO1 << 1);			// DIRECCION DEL ESCLAVO CON BIT DE LECTURA
				I2C_write('Y');						// ENVIA DATO
				I2C_stop();
			break;
			
			case '6':
				I2C_start();							// INICIA COMUNICACION I2C
				I2C_write(SLA_ESCLAVO2 << 1);			// DIRECCION DEL ESCLAVO CON BIT DE LECTURA
				I2C_write('Z');						// ENVIA DATO
				I2C_stop();								// TERMINA COMUNICACION I2C
			break;
			
			case '7':
				I2C_start();							// INICIA COMUNICACION I2C
				I2C_write(SLA_ESCLAVO2 << 1);			// DIRECCION DEL ESCLAVO CON BIT DE LECTURA
				I2C_write('Y');						// ENVIA DATO
				I2C_stop();								// TERMINA COMUNICACION I2C
			break;

			default: break;		
			}
		}else if (control == 0){
			I2C_start();							// INICIA COMUNICACION I2C
			I2C_write(SLA_ESCLAVO1 << 1);			// DIRECCION DEL ESCLAVO CON BIT DE LECTURA
			I2C_write('X');						// ENVIA DATO
			I2C_stop();								// TERMINA COMUNICACION I2C
			
			I2C_start();							// INICIA COMUNICACION I2C
			I2C_write(SLA_ESCLAVO2 << 1);			// DIRECCION DEL ESCLAVO CON BIT DE LECTURA
			I2C_write('X');						// ENVIA DATO
			I2C_stop();								// TERMINA COMUNICACION I2C
			txt_write_UART("AUTIO\n");
		}
		
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
		if (control == 1){
			if (recibido == '5') {
				PORTC |= (1 << PORTC0);					// ENCIENDE LA LUZ SI ESTA OSCURO
				PORTC |= (1 << PORTC1);					// ENCIENDE LA LUZ SI ESTA OSCURO
			}
			if (recibido == '4'){
				PORTC &= ~(1 << PORTC0);				// APAGA LA LUZ SI ESTA CLARO
				PORTC &= ~(1 << PORTC1);				// APAGA LA LUZ SI ESTA CLARO
			}
		}else{
			if (luz <= 100) {
				PORTC |= (1 << PORTC0);					// ENCIENDE LA LUZ SI ESTA OSCURO
				PORTC |= (1 << PORTC1);					// ENCIENDE LA LUZ SI ESTA OSCURO
				} else {
				PORTC &= ~(1 << PORTC0);				// APAGA LA LUZ SI ESTA CLARO
				PORTC &= ~(1 << PORTC1);				// APAGA LA LUZ SI ESTA CLARO
			}
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
		_delay_ms(100);
	}
}

ISR (USART_RX_vect){			//CADA VEZ QUE EL RX DETECTE UN VALOR, SE ACTIVA LA BANDERA
	flag = 1;					//Y EL VALOR SE GUARDA TEMPORALMENTE EN BUFFERRX
	bufferRX = UDR0;
	if (bufferRX != '\n' && bufferRX != '\r') {
		switch (bufferRX){
			case '0': control = 0; txt_write_UART("AUTO\n"); break;
			case '1': control = 1; txt_write_UART("MANUAL\n");	break;
			case '2': recibido = '2'; break;
			case '3': recibido = '3'; break;
			case '4': recibido = '4'; break;
			case '5': recibido = '5'; break;
			case '6': recibido = '6'; break;
			case '7': recibido = '7'; break;
			default: recibido = 0; break;
		}
	}
}
