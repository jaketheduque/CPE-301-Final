#ifndef WATER_SENSOR_H
#define WATER_SENSOR_H

#include "GPIO.h"

class WaterSensor {
    private:
        uint8_t _power_pin;
        uint8_t _analog_channel;
    public:
        WaterSensor(uint8_t power_pin, uint8_t analog_channel);

        uint8_t read();
};

#endif