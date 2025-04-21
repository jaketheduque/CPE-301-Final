#include "GPIO.h"

byte port_mappings[70] = {
  PORTE, PORTE, PORTE, PORTE, PORTG, PORTE, PORTH, PORTH, PORTH, PORTH, PORTB, PORTB, PORTB, PORTB, PORTJ, PORTJ, PORTH, PORTH, PORTD, PORTD, PORTD, PORTD, PORTA, PORTA, PORTA, PORTA, PORTA, PORTA, PORTA, PORTA, PORTC, PORTC, PORTC, PORTC, PORTC, PORTC, PORTC, PORTC, PORTD, PORTG, PORTG, PORTG, PORTL, PORTL, PORTL, PORTL, PORTL, PORTL, PORTL, PORTL, PORTB, PORTB, PORTB, PORTB, PORTF, PORTF, PORTF, PORTF, PORTF, PORTF, PORTF, PORTF, PORTK, PORTK, PORTK, PORTK, PORTK, PORTK, PORTK, PORTK
};
byte pin_mappings[70] = {
  0, 1, 4, 5, 5, 3, 3, 4, 5, 6, 4, 5, 6, 7, 1, 0, 1, 0, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 7, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7
}; 

volatile unsigned char* port[10] = {0x22, 0x25, 0x28, 0x2B, 0x2E, 0x31, 0x34, 0x102, 0x105, 0x108};
volatile unsigned char* port_ddr[10] = {0x21, 0x24, 0x27, 0x2A, 0x2D, 0x30, 0x33, 0x101, 0x104, 0x107};
volatile unsigned char* port_pin[10] = {0x20, 0x23, 0x26, 0x29, 0x2C, 0x2F, 0x32, 0x100, 0x103, 0x106};

void set_pinmode(byte pin, byte mode) {
  if (mode == OUTPUT) {
    *port_ddr[port_mappings[pin]] |= (0x01 << pin_mappings[pin]);
  } else {
    *port_ddr[port_mappings[pin]] &= ~(0x01 << pin_mappings[pin]);
  }
}

void write(byte pin, byte value) {
  if (value == HIGH) {
    *port[port_mappings[pin]] |= (0x01 << pin_mappings[pin]);
  } else {
    *port[port_mappings[pin]] &= ~(0x01 << pin_mappings[pin]);
  }
}

bool read(byte pin) {
  return (*port_pin[port_mappings[pin]] & (0x01 << pin_mappings[pin]));
}