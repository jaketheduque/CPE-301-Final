#include "DHT11.h"

DHT11::DHT11(uint8_t data_pin) {
    this->_data_pin = data_pin;
    this->_last_get_time = 0;
    set_pinmode(data_pin, INPUT);
}

void DHT11::begin() {
    // wait one second for sensor to initialize
    delay(1000);
    getData();
}

DHT11Data DHT11::getData() {
    if (millis() - _last_get_time < MIN_INTERVAL) {
        return _last_data;
    }
    _last_get_time = millis();

    // set pin LOW for 25ms to start communication with DHT11
    set_pinmode(_data_pin, OUTPUT);
    digital_write(_data_pin, LOW);
    _delay_ms(25);

    // wait for DHT to acknowledge
    set_pinmode(_data_pin, INPUT);
    while (digital_read(_data_pin));

    // wait 100us
    _delay_us(100);

    // disable interrupts as timing is critical
    cli();

    // wait for first bit
    while (digital_read(_data_pin));

    // begin collecting data
    int8_t i = 7;
    DHT11Data data;
    uint8_t value = 0;

    // int_RH;
    while (i >= 0) {
        // wait for beginning 50us start signal to finish
        while (!digital_read(_data_pin));

        // wait 30 us, if data is low, then 0, else it is 1
        _delay_us(30);
        if (digital_read(_data_pin)) {
            value |= (1 << i);
            _delay_us(40);
        }
        i--;
    }
    data.int_RH = value;
    i = 7;
    value = 0;

    // dec_RH
    while (i >= 0) {
        // wait for beginning 50us start signal to finish
        while (!digital_read(_data_pin));

        // wait 30 us, if data is low, then 0, else it is 1
        _delay_us(30);
        if (digital_read(_data_pin)) {
            value |= (1 << i);
            _delay_us(40);
        }
        i--;
    }
    data.dec_RH = value;
    i = 7;
    value = 0;

    // int_temp
    while (i >= 0) {
        // wait for beginning 50us start signal to finish
        while (!digital_read(_data_pin));

        // wait 30 us, if data is low, then 0, else it is 1
        _delay_us(30);
        if (digital_read(_data_pin)) {
            value |= (1 << i);
            _delay_us(40);
        }
        i--;
    }
    data.int_temp = value;
    i = 7;
    value = 0;

    // dec_temp
    while (i >= 0) {
        // wait for beginning 50us start signal to finish
        while (!digital_read(_data_pin));

        // wait 30 us, if data is low, then 0, else it is 1
        _delay_us(30);
        if (digital_read(_data_pin)) {
            value |= (1 << i);
            _delay_us(40);
        }
        i--;
    }
    data.dec_temp = value;
    i = 7;
    value = 0;

    // checksum
    while (i >= 0) {
        // wait for beginning 50us start signal to finish
        while (!digital_read(_data_pin));

        // wait 30 us, if data is low, then 0, else it is 1
        _delay_us(30);
        if (digital_read(_data_pin)) {
            value |= (1 << i);
            _delay_us(40);
        }
        i--;
    }
    data.checksum = value;

    // reenable interrupts
    sei();

    _last_data = data;
    return data;
}

uint8_t DHT11::getTemperature() {
    return getData().int_temp;
}

float DHT11::getFloatTemperature() {
    DHT11Data data = getData();

    float temp = data.int_temp;
    temp += ((float) data.dec_temp / 256.0);

    return temp;
}

uint8_t DHT11::getHumidity() {
    return getData().int_RH;
}

float DHT11::getFloatHumidity() {
    DHT11Data data = getData();

    float temp = data.int_RH;
    temp += ((float) data.dec_RH / 256.0);

    return temp;
}