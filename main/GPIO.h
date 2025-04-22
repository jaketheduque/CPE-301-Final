#ifndef GPIO_H
#define GPIO_H

#include <Arduino.h>
#include "Constants.h"

extern byte port_mappings[NUM_PINS];
extern byte pin_mappings[NUM_PINS]; 

extern volatile unsigned char *port[NUM_PORTS];
extern volatile unsigned char *port_ddr[NUM_PORTS];
extern volatile unsigned char *port_pin[NUM_PORTS];

extern bool analog_ready;

void set_pinmode(byte pin, byte mode);
void digital_write(byte pin, byte value);
bool digital_read(byte pin);

void analog_init();
void analog_write(byte channel, byte value);
byte analog_read(byte channel);

#endif