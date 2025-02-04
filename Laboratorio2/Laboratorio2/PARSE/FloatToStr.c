/*
 * FloatToStr.c
 *
 * Created: 3/02/2025 23:47:23
 *  Author: jaidy
 */ 
#include "FloatToStr.h"

void float_to_string(float num, char *buffer, int precision) {
	// Parte entera
	int integer_part = (int)num;
	
	// Parte decimal
	float decimal_part = num - integer_part;
	
	// Convertir la parte entera a cadena
	char int_buffer[16]; // Buffer para la parte entera
	snprintf(int_buffer, sizeof(int_buffer), "%d", integer_part);
	
	// Convertir la parte decimal a cadena
	char dec_buffer[16]; // Buffer para la parte decimal
	for (int i = 0; i < precision; i++) {
		decimal_part *= 10;
	}
	snprintf(dec_buffer, sizeof(dec_buffer), "%d", (int)decimal_part);
	
	// Combinar ambas partes en el buffer final
	snprintf(buffer, 32, "%s.%s", int_buffer, dec_buffer);
}
