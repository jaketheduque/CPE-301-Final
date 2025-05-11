# CPE 301 - Final Project
The water cooler created in this project aims to reduce ambient air temperature using evaporative cooling. To achieve this, the cooler uses a push button, potentiometer, LEDs, water sensor, fan motor, stepper motor, temperature/humidity sensor, real-time module, and a display. The video demonstration can be found [here](https://youtu.be/OoSIE_4rT5M), and the `report.pdf` file contains more general information on how the cooler works at a higher level.

# Custom Implementations
As a personal challenge, I decided to try using *none* of the Arduino libraries, and instead, write my own implementations for all components of this project. Not all functions are listed below, only the ones containing important functionality.

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
### `void send_instruction(uint8_t data)`
Sends an 8-bit instruction to the display by setting the register select line LOW, setting the 8 data lines according to the `data` parameter, and then toggling the enable line.

### `void set_cursor(uint8_t row, uint8_t col)`
Moves the display cursor to the specificed row and column by sending either a `0x80 | col` instruction for the first row, or a `0xC0 | col` instruction for the second row.

### `void print_char(uint8_t data)`
Prints a single character to the display at the current cursor position. This is done by setting the register select line HIGH, setting the 8 data lines according to the `data` parameter, and toggling the enable line.

### `print(const char *data)`
Prints every character in the provided `data` string to the display using the `print_char` fuction.

### `void clear()`
Clears all data currently on the screen and also resets the cursor position to (0,0) by sending a `0x01` instruction using `send_instruction`.

## I2C
The ATMega2560 microprocessor used in this project has a built-in Two-Wire Interface (TWI) which can be configured for I2C communication. The functions below configure and coordinate I2C communication using the TWI module and its associated registers.

### `void begin()`
Initializes the TWI module on the ATMega2560 processor with a ~30kHz bit rate.

### `void start(uint8_t addr)`
Starts communication with a single slave device on the I2C bus in read or write mode (depending on bit 7 in the `addr` parameter).

### `void send_byte(uint8_t data)`
Sends a byte of data to the slave device currently being communicated with, and then waits for the acknowledgment from the device.

### `void send_data(uint8_t *data, uint8_t len)`
Sends a sequence of bytes, utilizing the `sendByte` function in a loop until `len` bytes have been sent.

### `uint8_t receive_byte()`
Receives a byte of data from the slave device currently being communicated with.

**Note:** Functions `repeat_start` and `receive_last_byte` are also implemented, since there are minor differences in the data sent between data sent at the beginning and the last byte data (ex. after receiving the last byte, a NACK must be sent over the SDA line instead of a ACK)

## DS1307 Module
The DS1307 RTC module communicates over I2C, and the functions below utilize the custom I2C library to handle the bulk of I2C communication nuances.

### `tm DS1307::getDatetime()`
Returns a `tm` with the current time on the DS1307 module. The process starts by setting the DS1307 register pointer to `0x00` which contains the current seconds. Each byte of data retreived from the DS1307 automatically moves the register pointer forward to the next register. As each time place (seconds, minutes, hours, etc.) is retreived, the corresponding field in the `tm` struct is set, and after all fields have been filled, the `tm` struct is returned.

**Note:** This should probably be changed to take in a `tm` pointer as a parameter to prevent funky scope issues.

### `void setDateTime(char input[20])`
Takes in a ISO8601 formatted string (YYYY-MM-DDTHH-mm-ss) and sets the DS1307 date registers to change the current time on the module. Similar to when reading time from the DS1307, when a byte is written to a register, the register pointer is automatically incremented to the next register after each write.