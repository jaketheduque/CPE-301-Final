#ifndef I2C_H
#define I2C_H

#include "GPIO.h"
#include "MyArduino.h"

class I2C {
    public:
        static void begin();
        static void start(uint8_t addr);
        static void repeatStart(uint8_t addr);
        static void stop();
        static void sendByte(uint8_t data);
        static void sendData(uint8_t *data, uint8_t len);
        static uint8_t receiveByte();
        static uint8_t receiveLastByte();
};

#endif