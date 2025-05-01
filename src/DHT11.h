#ifndef DHT11_H
#define DHT11_H

#define MIN_INTERVAL 2000 // minimum time to wait before getting a new reading from the sensor in millis

#include <avr/interrupt.h>
#include <util/delay.h>

#include "GPIO.h"
#include "Serial.h"
#include "Timer.h"

struct DHT11Data {
    uint8_t int_RH;
    uint8_t dec_RH;
    uint8_t int_temp;
    uint8_t dec_temp;
    uint8_t checksum;
};

class DHT11 {
    private:
        uint8_t _data_pin;
        DHT11Data _last_data;
        uint64_t _last_get_time;
        
    public:
        DHT11(uint8_t data_pin);

        void begin();

        DHT11Data getData();
        
        uint8_t getHumidity();
        float getFloatHumidity();

        uint8_t getTemperature();
        float getFloatTemperature();
};

#endif