#include <Arduino.h>
#include "Port.h"

Port::Port(unsigned char* port, unsigned char* port_ddr, volatile unsigned char* port_pin) {
  this->port = port;
  this->port_ddr = port_ddr;
  this->port_pin = port_pin;
}

void Port::set_pinmode(byte pin, byte mode) {
  if (mode == OUTPUT) {
    *port_ddr |= (0x01 << pin);
  } else {
    *port_ddr &= ~(0x01 << pin);
  }
}

void Port::write(byte pin, byte value) {
  if (value == HIGH) {
    *port |= (0x01 << pin);
  } else {
    *port &= ~(0x01 << pin);
  }
}

bool Port::read(byte pin) {
  return (*port_pin & ~(0x01 << pin));
}