/*
 * Proyecto1.3.c
 *
 * Created: 25/02/2025 23:32:39
 * Author : jaidy
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "I2C/I2C_SLAVE.h"
#include "ADC/ADC.h"
#include "PWM1/PWM1.h"
#include "PWM2/PWM2.h"

#define THRESHOLD 15

volatile uint8_t dato_recibido;
uint8_t dato_a_enviar = 1;
float mostrar = 1;

int signal = 0;

void setupServos() {
	// Inicializa PWM1A (Servo 1) en modo FAST con ICR1 como TOP, prescaler 8, frecuencia 50 Hz (TOP=19999)
	init_PWM1A(0, 6, 8, 19999);
	
	// Inicializa PWM2A (Servo 2) en modo no invertido, prescaler 8
	init_PWM2A(0, 3, 1024);
}

void moveServos(int signal) {
	if (signal < THRESHOLD) {
		// Ambos servos a 90° (1500us de pulso)
		duty_cycle1A(3150);
		duty_cycle2A(21);
	} else {
		// Servo 1 a 0° (1000us de pulso), Servo 2 a 180° (2000us de pulso)
		duty_cycle1A(5100);
		duty_cycle2A(6);
	}
}

void controlServos(char dato_recibido, int dato_enviado) {
	switch (dato_recibido) {
		case 'Y':
			moveServos(100); // Abrir ventanas
		break;
		case 'Z':
			moveServos(0); // Cerrar ventanas
		break;
		case 'X':
			moveServos(dato_enviado/255.00*100.00); // Usar el dato del sensor
		break;
		default:
		// Ignorar cualquier otro valor
		break;
	}
}


int main(void){
	I2C_esclavo_init();			// Inicializa el esclavo
	initADC();
	setupServos();
	sei();						// Habilita interrupciones globales
	while (1){
		dato_a_enviar = ADC_CONVERT(0);
		/*
		signal = 10; // Ejemplo de señal, cámbiala según sea necesario
		_delay_ms(1000);
		moveServos(signal);
		signal = 30; // Ejemplo de señal, cámbiala según sea necesario
		_delay_ms(1000);
		moveServos(signal);
		*/
		controlServos(dato_recibido, dato_a_enviar);
	}
}

ISR(TWI_vect) {
	switch (TWSR & 0xF8) {
		case 0x80:				// Dato recibido de maestro
		dato_recibido = TWDR;
		//PORTB = dato_recibido;
		break;
		case 0xA8:				// Maestro solicita lectura
		TWDR = dato_a_enviar;	// Carga el dato a enviar
		break;
	}
	I2C_reset();				// Reinicia I2C para recibir más datos
}
