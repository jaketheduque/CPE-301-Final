#include "GPIO.h"

bool analog_ready = false;

void set_pinmode(uint8_t pin, uint8_t mode) {
  if (mode == OUTPUT) {
    *port_ddr[port_mappings[pin]] |= (1 << pin_mappings[pin]);
  } else if (mode == INPUT_PULLUP) {
    *port_ddr[port_mappings[pin]] |= (1 << pin_mappings[pin]);
    *port[port_mappings[pin]] |= (1 << pin_mappings[pin]);
  } else {
    *port_ddr[port_mappings[pin]] &= ~(1 << pin_mappings[pin]);
  }
}

void digital_write(uint8_t pin, uint8_t value) {
  if (value != LOW) {
    *port[port_mappings[pin]] |= (1 << pin_mappings[pin]);
  } else {
    *port[port_mappings[pin]] &= ~(1 << pin_mappings[pin]);
  }
}

bool digital_read(uint8_t pin) {
  return (*port_pin[port_mappings[pin]] & (1 << pin_mappings[pin]));
}

void analog_init() {
  // clear bit 6 to 0 to disable the ADC trigger mode
  ADCSRA &= ~(1 << 6);

  // clear bit 5 to 0 to disable the ADC interrupt
  ADCSRA &= ~(1 << 5);

  // clear bit 0-2 to 0 to set prescaler selection to slow reading
  ADCSRA &= 0x08;

  // clear bit 3 to 0 to reset the channel and gain bits
  ADCSRB &= ~(1 << 3);

  // clear bit 2-0 to 0 to set free running mode
  ADCSRB &= 0x08;

  // clear bit 7 to 0 for AVCC analog reference
  ADMUX &= ~(1 << 7);

  // set bit 6 to 1 for AVCC analog reference
  ADMUX|= (1 << 6);

  // set bit 5 for left adjust result
  ADMUX|= (1 << 5);

  // clear bit 4-0 to 0 to reset the channel and gain bits
  ADMUX&= 0xE0;

  analog_ready = true;
}

void analog_write(uint8_t pin, uint8_t value) {
  if (pin > 13) { // pwm pins are D0-D13
    return;
  }

  // enable fast pwm mode
  
}

uint8_t analog_read(uint8_t channel) {
  if (!analog_ready) {
    analog_init();
  }

  // set bit 7 to 1 to enable the ADC
  ADCSRA |= (1 << 7);

  // clear the channel selection bits (MUX 5:0)
  ADMUX &= ~(1 << 0);
  ADMUX &= ~(1 << 1);
  ADMUX &= ~(1 << 2);
  ADMUX &= ~(1 << 3);
  ADMUX &= ~(1 << 4);
  ADCSRB &= ~(1 << 3);

  // set the channel selection bits (refer to table 26-4)
  ADMUX |= (0x07 & channel);
  ADCSRB |= (0x08 & channel);

  // set bit 6 of ADCSRA to 1 to start a conversion
  ADCSRA |= (1 << 6);

  // wait for the conversion to complete
  while ((ADCSRA & 0x40) != 0);

  uint8_t val = (uint8_t) ADCH;

  // disable the ADC
  ADCSRA &= ~(1 << 7);

  return val;
}