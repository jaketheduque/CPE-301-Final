#include "I2C.h"

void I2C::begin() {
    // set no prescaler and bit rate register to 255
    // ends up being ~30kHz bit rate
    TWBR = 0xFF;
    TWSR &= ~((1<<TWPS1)|(1<<TWPS0));
}

void I2C::start(uint8_t addr) {
    // send start condition
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

    // wait for TWINT set
    while (!(TWCR & (1<<TWINT)));

    // load addr (with r/w bit) into TWDR register and clear TWINT to start transmission
    TWDR = addr;
    TWCR = (1<<TWINT)|(1<<TWEN);

    // wait for ACK from receiver
    while (!(TWCR & (1<<TWINT)));
}

void I2C::repeatStart(uint8_t addr) {
    // send restart condition
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

    // wait for TWINT set
    while (!(TWCR & (1<<TWINT)));

    // load addr (with r/w bit) into TWDR register and clear TWINT to start transmission
    TWDR = addr;
    TWCR = (1<<TWINT)|(1<<TWEN);

    // wait for ACK from receiver
    while (!(TWCR & (1<<TWINT)));
}

void I2C::stop() {
    // transmit stop condition
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void I2C::sendByte(uint8_t data) {
    // load data into TWDR and then clear TWINT to start data transmission
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);

    // wait for ACK from receiver
    while (!(TWCR & (1<<TWINT)));
}

void I2C::sendData(uint8_t *data, uint8_t len) {
    for (int i = 0 ; i < len ; i++) {
        sendByte(data[i]);
    }
}

uint8_t I2C::receiveByte() {
    // receive data byte and return ACK
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);

    // wait for data to be ready
    while (!(TWCR & (1<<TWINT)));

    return TWDR;
}

uint8_t I2C::receiveLastByte() {
    // start receiving data and return NACK
    TWCR = TWCR=(1<<TWINT)|(1<<TWEN);

    // wait for data to be ready
    while (!(TWCR & (1<<TWINT)));

    return TWDR;
}