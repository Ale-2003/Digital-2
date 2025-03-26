//********************************************************************************
/* Universidad del Valle de Guatemala
 * IE3054: Electrónica Digital 2
 * Autor: Alejandra Marcos
 * Laboratorio6.c
 *
 * Created: 20/03/2025 19:16:54
 * Author: jaidy
 */
//********************************************************************************

// LIBRERÍAS
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "IntExt/IntExt.h"
#include "UART/UART.h"

// DEFINICIONES
#define FALLING_EDGE 1  // Si no está definido en IntExt.h

// VARIABLES GLOBALES
volatile uint8_t flag_interrupt = 0;

// FUNCIONES

int main(void) {
    initPinChange1(falling_edge);  // INTERRUPCIONES PC0 - PC5
    initUART(fast, 9600);
    sei(); // Habilitar interrupciones globales
    while (1) {
        if (flag_interrupt) {
            _delay_ms(100);  // Se aplica el retraso fuera de la ISR
            
            if (!(PINC & (1 << PC0))) write_UART('A');
            if (!(PINC & (1 << PC1))) write_UART('B');
            if (!(PINC & (1 << PC2))) write_UART('U');
            if (!(PINC & (1 << PC3))) write_UART('D');
            if (!(PINC & (1 << PC4))) write_UART('L');
            if (!(PINC & (1 << PC5))) write_UART('R');

            flag_interrupt = 0; // Limpiar la bandera
        }
    }
}

// ISR PARA INTERRUPCIONES EN PC0 - PC5
ISR (PCINT1_vect) {
    flag_interrupt = 1;  // Indicar que hubo una interrupción
}
