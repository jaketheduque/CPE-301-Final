#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>

#include "MyArduino.h"

void begin_serial(uint8_t channel, uint16_t baud);
void send(uint8_t channel, unsigned char data);
void printChar(uint8_t channel, const char data);
void print(uint8_t channel, const char *data);
void println(uint8_t channel, const char *data);

#endif