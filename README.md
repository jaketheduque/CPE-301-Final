# CPE 301 - Final Project
This project involves several sensors and motors blah blah blah

# Custom Implementations
As a personal challenge, I decided to try using *none* of the Arduino libraries, and instead, write my own.

## GPIO
### `void set_pinmode(byte pin, byte mode)`
### `void digital_write(byte pin, byte value)`
### `bool digital_read(byte pin)`

### `void analog_init()`
### `void analog_write(byte channel, byte value)`
### `byte analog_read(byte channel)`

## Stepper Motor
### `void energize_step(byte step)`
### `void cw_step()`
### `void ccw_step()`
### `void rotate(int rotations)`

## Timer

## DHT11

## 1602 Display

## SPI (Real Time Module)