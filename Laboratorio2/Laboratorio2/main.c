//********************************************************************************
/* Universidad del Valle de Guatemala
 * IE3054: Electronica digital 2
 * Autor: Alejandra Marcos
 * Laboratorio2.c
 *
 * Created: 29/01/2025 22:58:24
 * Author : jaidy
 */
 //********************************************************************************

//LIBRERIAS
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "LCD/LCD_16x2_8b.h"
#include "ADC/ADC.h"
#include "UART/UART.h"
#include "PARSE/FloatToStr.h"

//VARIABLES
float Value1 = 0;
float Value2 = 0;
char b1[16];
char b2[16];
int cont = 0;
char contador[10];
int flag = 1;
volatile char bufferRX;

//FUNCIONES

int main(void){
	initADC();
    lcd_init();
    lcd_command(0x80);
    lcd_print("S1:   S2:   S3:  ");
	initUART(fast, 9600);
	sei();
    while (1){
		Value1 = (ADC_CONVERT(0)*5.0)/1023.0;
		float_to_string(Value1, b1, 2);
		Value2 = (ADC_CONVERT(1)*5.0)/1023.0;
		float_to_string(Value2, b2, 2);
		
		lcd_set_cursor(1, 0);
		lcd_print(b1);
		lcd_set_cursor(1, 4);
		lcd_print("V");
		
		lcd_set_cursor(1, 6);
		lcd_print(b2);
		lcd_set_cursor(1, 10);
		lcd_print("V");
		
		while (flag == 1){
			switch (bufferRX){
				case '+': cont++; flag = 0; break;
				case '-': cont--; flag = 0; break;
				default: flag = 0; break;
			}
		}		
		sprintf(contador, "%d", cont);
		lcd_set_cursor(1, 12);
		lcd_print(contador);
    }
}

ISR (USART_RX_vect){			//CADA VEZ QUE EL RX DETECTE UN VALOR, SE ACTIVA LA BANDERA
	flag = 1;					//Y EL VALOR SE GUARDA TEMPORALMENTE EN BUFFERRX
	bufferRX = UDR0;
}