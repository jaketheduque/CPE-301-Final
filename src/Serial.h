#ifndef SERIAL_H
#define SERIAL_H

#include <avr/io.h>

#include "MyArduino.h"

class Serial {
    public:
        static void begin_serial(uint8_t channel, uint16_t baud);
        static bool available(uint8_t channel);

        static unsigned char receive(uint8_t channel);

        static void send(uint8_t channel, unsigned char data);
        static void printChar(uint8_t channel, const char data);
        static void print(uint8_t channel, const char *data);
        static void println(uint8_t channel, const char *data);
};


#endif