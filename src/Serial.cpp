#include "Serial.h"

/**
 * TODO This still needs to have multiple channel support and baud rate selection added
 */
void begin_serial(uint8_t channel, uint16_t baud) {
    /* Set baud rate */
    UBRR0H = (unsigned char) (baud>>8);
    UBRR0L = (unsigned char) baud;

    /* Enable receiver and transmitter */
    sbi(UCSR0B, RXEN0);
    sbi(UCSR0B, TXEN0);

    /* Set frame format: 8 bit data, 1 stop bit */
    sbi(UCSR0C, UCSZ00);
    sbi(UCSR0C, UCSZ01);
}

/**
 * TODO This still needs to have multiple channel support added
 */
void send(uint8_t channel, unsigned char data) {
    // wait for channel to be available
    while (!(UCSR0A & (1<<UDRE0)));

    UDR0 = data;
}

/**
 * TODO This still needs to have multiple channel support added
 */
void printChar(uint8_t channel, const char data) {
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}

/**
 * TODO This still needs to have multiple channel support added
 */
void print(uint8_t channel, const char *data) {
    int i = 0;
    while (data[i] != '\0') {
        // wait for channel to be available
        while (!(UCSR0A & (1<<UDRE0)));
        UDR0 = data[i];
        i++;
    }
}

/**
 * TODO This still needs to have multiple channel support added
 */
void println(uint8_t channel, const char *data) {
    print(channel, data);
    send(channel, '\n');
}