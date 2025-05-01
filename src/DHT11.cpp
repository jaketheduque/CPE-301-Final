#include "DHT11.h"

DHT11::DHT11(uint8_t data_pin) {
    this->data_pin = data_pin;
    set_pinmode(data_pin, INPUT);
}

DHT11Data DHT11::getData() {
    // disable interrupts as timing is critical
    cli();

    // set pin LOW for 25ms to start communication with DHT11
    set_pinmode(data_pin, OUTPUT);
    digital_write(data_pin, LOW);
    _delay_ms(25);

    // wait for DHT to acknowledge
    set_pinmode(data_pin, INPUT);
    while (digital_read(data_pin));

    // wait 100us and wait for first bit
    _delay_us(100);
    while (digital_read(data_pin));

    // begin collecting data
    int8_t i = 7;
    DHT11Data data;
    uint8_t value = 0;

    // int_RH;
    while (i >= 0) {
        // wait for beginning 50us start signal to finish
        while (!digital_read(data_pin));

        // wait 30 us, if data is low, then 0, else it is 1
        _delay_us(30);
        if (digital_read(data_pin)) {
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
        while (!digital_read(data_pin));

        // wait 30 us, if data is low, then 0, else it is 1
        _delay_us(30);
        if (digital_read(data_pin)) {
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
        while (!digital_read(data_pin));

        // wait 30 us, if data is low, then 0, else it is 1
        _delay_us(30);
        if (digital_read(data_pin)) {
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
        while (!digital_read(data_pin));

        // wait 30 us, if data is low, then 0, else it is 1
        _delay_us(30);
        if (digital_read(data_pin)) {
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
        while (!digital_read(data_pin));

        // wait 30 us, if data is low, then 0, else it is 1
        _delay_us(30);
        if (digital_read(data_pin)) {
            value |= (1 << i);
            _delay_us(40);
        }
        i--;
    }
    data.checksum = value;

    // wait for data level to go HIGH
    _delay_us(50);

    // reenable interrupts
    sei();

    return data;
}