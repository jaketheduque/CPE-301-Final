#ifndef GPIO_H
#define GPIO_H

#include <Arduino.h>
#include "Constants.h"

extern byte port_mappings[70];
extern byte pin_mappings[70]; 

extern volatile unsigned char* port[10];
extern volatile unsigned char* port_ddr[10];
extern volatile unsigned char* port_pin[10];

void set_pinmode(byte pin, byte mode);
void write(byte pin, byte value);
bool read(byte pin);

#endif