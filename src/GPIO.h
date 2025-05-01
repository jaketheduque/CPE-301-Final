#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>
#include "MyArduino.h"

extern bool analog_ready;

void set_pinmode(uint8_t pin, uint8_t mode);
void digital_write(uint8_t pin, uint8_t value);
bool digital_read(uint8_t pin);

void analog_init();
void analog_write(uint8_t channel, uint8_t value);
uint8_t analog_read(uint8_t channel);

#endif