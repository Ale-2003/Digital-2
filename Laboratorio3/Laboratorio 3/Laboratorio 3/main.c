//********************************************************************************
/* Universidad del Valle de Guatemala
 * IE3054: Electronica digital 2
 * Autor: Alejandra Marcos
 * Laboratorio 3.c
 *
 * Created: 6/02/2025 16:10:38
 * Author : jaidy
 */ 
 //********************************************************************************

 //LIBRERIAS
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#include "SPI/SPI_MASTER.h"
#include "UART/UART.h"

//VARIABLES
float voltaje1 = 0;
float voltaje2 = 0;
char buffer1[5];
char buffer2[5];
int flag = 1;
volatile char bufferRX;

//FUNCIONES

int main(void){
	initUART(fast, 9600);				//INICIALIZA EL UART A 9600 BAUDIOS
    SPI_MasterInit();					//INICIALIZA EL SPI
	DDRD = 0xFC;						//PUERTO D COMO SALIDA PD2-PD7
	DDRB |= (1 << DDB1) | (1 << DDB0);  //PUERTO B COMO SALIDA PB0-PB1
	sei();
    while (1) {
		SPI_MasterTransmit('A');					    //ENVIA EL DATO AL ESCLAVO
		uint16_t received_data = SPI_MasterReceive();   //RECIBE EL DATO DEL ESCLAVO	
		voltaje1 = (received_data/255.0)*5;			    //CONVIERTE A VOLTAJE
		dtostrf(voltaje1, 1, 2, buffer1);			    //CONVIERTE A STRING
		PORTB |= (1 << DD_SS);						    //DESELECIONA EL ESCLAVO
		txt_write_UART("Voltaje 1: ");
		txt_write_UART(buffer1);
		txt_write_UART("  ");						    //ENVIA EL DATO POR UART
		
		SPI_MasterTransmit('B');						//ENVIA UN DATO AL ESCLAVO
		uint16_t received_data1 = SPI_MasterReceive();  //RECIBE EL DATO DEL ESCLAVO
		voltaje2 = received_data1/255.0;				//CONVIERTE A VOLTAJE
		dtostrf(voltaje2, 1, 2, buffer2);				//CONVIERTE A STRING
		PORTB |= (1 << DD_SS);							//DESELECIONA EL ESCLAVO
		txt_write_UART("Voltaje 2: ");
		txt_write_UART(buffer2);
		txt_write_UART("\n");							//ENVIA EL DATO POR UART
		
		while (flag == 1){
			SPI_MasterTransmit(bufferRX);				//ENVIA UN DATO AL ESCLAVO
			PORTB |= (1 << DD_SS);						// DESELECIONA EL ESCLAVO
			PORTB = (PORTB & 0xFC) | (bufferRX & 0x03);	//
			PORTD = (PORTD & 0x03) | (bufferRX & 0xFC); //MUESTRA EL DATO ENVIADO
			flag = 0;
		}
		
    }
}

ISR (USART_RX_vect){			//CADA VEZ QUE EL RX DETECTE UN VALOR, SE ACTIVA LA BANDERA
	flag = 1;					//Y EL VALOR SE GUARDA TEMPORALMENTE EN BUFFERRX
	bufferRX = UDR0;
}