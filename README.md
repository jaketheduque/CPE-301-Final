# CPE 301 - Final Project
This project involves several sensors and motors blah blah blah

# Custom Implementations
As a personal challenge, I decided to try using *none* of the Arduino libraries, and instead, write my own. Not all functions are listed below, only the ones containing important functionality.

## GPIO
### `void set_pinmode(uint8_t pin, uint8_t mode)`
Sets the corresponding `DDR` register bit to:
- 0 if INPUT
- 1 if OUTPUT

In addition, the corresponding `DDR` and `PORT` register bits will both be set if `INPUT_PULLUP` mode is desired.
### `void digital_write(uint8_t pin, uint8_t value)`
Sets or clears the corresponding `PORT` register bit depending on `value`.

### `bool digital_read(uint8_t pin)`
Reads the current digital value from the corresponding `PIN` register bit.

### `void analog_init()`
Configures `ADCSRA`, `ADCSRB`, and `ADMUX` registers for analog-to-digital conversion. Sets reading to left justification.

### `void analog_write(uint8_t channel, uint8_t value)`
TODO

### `uint8_t analog_read(uint8_t channel)`
Begins ADC conversion on specified channel and returns the `ADCH` register (top 8 bits of result).

## Stepper Motor
### `void energize_step(uint8_t step)`
Activates the correct stators for the step passed in. 

**Note:** Currently configured to run in full-step mode, with 4 steps in a cycle.

### `void cw_step()`
Moves the motor one step counter-clockwise.

### `void ccw_step()`
Moves the motor one step clockwise.

### `void rotate(int rotations)`
Converts the number of rotations to number of steps, before looping `cw_step()` or `ccw_step()` to achieve desired rotation.

**Note:** Currently only configured to run at a single speed.

## Timer
Much of this was inspired by the official Arduino timer implementation, including the `TIMER0_OVF_vect` interrupt that increments `timer0_millis`, `timer0_fract`, and `timer0_overflow_count`.

`TIMER0` is an 8-bit timer configured with a 64 prescaler. This means that `TIMER0_OVF_vect` is run every 16,384 clock cycles (most of the time), or about once every millisecond.

### `uint64_t millis()`
Returns `timer0_millis` (approx. how many milliseconds since the program has started).

### `void delay(uint32_t duration)`
Delays for `duration` milliseconds by looping until the number of milliseconds since the function call is greater than `duration`.

## DHT11
### `DHT11Data getData()`
Requests a 40-bit packet from the DHT11 sensor and parses the information received into a `DHT11Data` which is returned.

**Note:** The checksum value is retreived from the sensor, but no logic is currently in place to check for errors in the packet.

## 1602 Display

## SPI (Real Time Module)