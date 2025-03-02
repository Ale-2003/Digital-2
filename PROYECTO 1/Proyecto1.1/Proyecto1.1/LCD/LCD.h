/*
 * LCD.h
 *
 * Created: 11/02/2025 21:45:07
 *  Author: jaidy
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>

#define RS PD2
#define RW PD3
#define E  PB4
#define LCD_PORT PORTD
#define LCD_DDR DDRD
#define LCD_PORTB PORTB
#define LCD_DDRB DDRB

void lcd_command(unsigned char cmd);

void lcd_init(void);

void lcd_data(unsigned char data);

void lcd_print(char *str);

void lcd_clear(void);

void lcd_set_cursor(uint8_t row, uint8_t col);

#endif /* LCD_H_ */