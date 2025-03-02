/*
 * TSL2561_I2C.c
 *
 * Created: 27/02/2025 18:46:18
 *  Author: jaidy
 */ 
#include "TSL2561_I2C.h"

void tsl2561_init() {
	I2C_start();
	I2C_write(TSL2561_ADDR << 1); // Dirección del esclavo en modo escritura
	I2C_write(TSL2561_COMMAND | TSL2561_CONTROL);
	I2C_write(0x03); // Power ON
	I2C_stop();

	I2C_start();
	I2C_write(TSL2561_ADDR << 1);
	I2C_write(TSL2561_COMMAND | TSL2561_TIMING);
	I2C_write(0x02); // Medium gain, 402ms integration time
	I2C_stop();
}

uint16_t tsl2561_read_luminosity() {
	uint16_t data0;

	I2C_start();
	I2C_write(TSL2561_ADDR << 1); // Dirección del esclavo en modo escritura
	I2C_write(TSL2561_COMMAND | TSL2561_DATA0LOW);
	
	I2C_start();
	I2C_write((TSL2561_ADDR << 1) | 0x01); // Dirección del esclavo en modo lectura

	uint8_t low = I2C_read_ack();
	uint8_t high = I2C_read_nack();

	I2C_stop();

	data0 = (high << 8) | low;
	return data0;
}