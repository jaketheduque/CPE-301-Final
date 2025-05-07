#include "WaterSensor.h"

WaterSensor::WaterSensor(uint8_t power_pin, uint8_t analog_channel) {
    _power_pin = power_pin;
    _analog_channel = analog_channel;

    set_pinmode(power_pin, OUTPUT);
    digital_write(_power_pin, LOW);
}

uint8_t WaterSensor::read() {
    digital_write(_power_pin, HIGH);
    uint8_t val = analog_read(_analog_channel);
    digital_write(_power_pin, LOW);
    return val;
}