#ifndef PORT_H
#define PORT_H

#include "Constants.h"

class Port {
  private:
    volatile unsigned char* port;
    volatile unsigned char* port_ddr;
    volatile unsigned char* port_pin;
  public:
    Port(unsigned char* port, unsigned char* port_ddr, volatile unsigned char* port_pin);

    void set_pinmode(byte pin, byte mode);
    void write(byte pin, byte value);
    bool read(byte pin);
};

#endif