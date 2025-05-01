#ifndef DHT11_H
#define DHT11_H

#include <avr/interrupt.h>
#include <util/delay.h>

#include "GPIO.h"
#include "Serial.h"

struct DHT11Data {
    uint8_t int_RH;
    uint8_t dec_RH;
    uint8_t int_temp;
    uint8_t dec_temp;
    uint8_t checksum;
};

class DHT11 {
    private:
        uint8_t data_pin;
        
    public:
        DHT11(uint8_t data_pin);

        DHT11Data getData();
        float getHumidity();
        float getTemperature();
};

#endif