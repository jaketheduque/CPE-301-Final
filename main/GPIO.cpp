#include "GPIO.h"

byte port_mappings[NUM_PINS] = {
  PORTE_INDEX, PORTE_INDEX, PORTE_INDEX, PORTE_INDEX, PORTG_INDEX, PORTE_INDEX, PORTH_INDEX, PORTH_INDEX, PORTH_INDEX, PORTH_INDEX,
  PORTB_INDEX, PORTB_INDEX, PORTB_INDEX, PORTB_INDEX, PORTJ_INDEX, PORTJ_INDEX, PORTH_INDEX, PORTH_INDEX, PORTD_INDEX, PORTD_INDEX, 
  PORTD_INDEX, PORTD_INDEX, PORTA_INDEX, PORTA_INDEX, PORTA_INDEX, PORTA_INDEX, PORTA_INDEX, PORTA_INDEX, PORTA_INDEX, PORTA_INDEX, 
  PORTC_INDEX, PORTC_INDEX, PORTC_INDEX, PORTC_INDEX, PORTC_INDEX, PORTC_INDEX, PORTC_INDEX, PORTC_INDEX, PORTD_INDEX, PORTG_INDEX, 
  PORTG_INDEX, PORTG_INDEX, PORTL_INDEX, PORTL_INDEX, PORTL_INDEX, PORTL_INDEX, PORTL_INDEX, PORTL_INDEX, PORTL_INDEX, PORTL_INDEX, 
  PORTB_INDEX, PORTB_INDEX, PORTB_INDEX, PORTB_INDEX, PORTF_INDEX, PORTF_INDEX, PORTF_INDEX, PORTF_INDEX, PORTF_INDEX, PORTF_INDEX, 
  PORTF_INDEX, PORTF_INDEX, PORTK_INDEX, PORTK_INDEX, PORTK_INDEX, PORTK_INDEX, PORTK_INDEX, PORTK_INDEX, PORTK_INDEX, PORTK_INDEX
};
byte pin_mappings[NUM_PINS] = {
  0, 1, 4, 5, 5, 3, 3, 4, 5, 6, 4, 5, 6, 7, 1, 0, 1, 0, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 7, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7
}; 

volatile unsigned char *port[NUM_PORTS] = {0x22, 0x25, 0x28, 0x2B, 0x2E, 0x31, 0x34, 0x102, 0x105, 0x108, 0x10B};
volatile unsigned char *port_ddr[NUM_PORTS] = {0x21, 0x24, 0x27, 0x2A, 0x2D, 0x30, 0x33, 0x101, 0x104, 0x107, 0x10A};
volatile unsigned char *port_pin[NUM_PORTS] = {0x20, 0x23, 0x26, 0x29, 0x2C, 0x2F, 0x32, 0x100, 0x103, 0x106, 0x109};

bool analog_ready = false;

void set_pinmode(byte pin, byte mode) {
  if (mode == OUTPUT) {
    *port_ddr[port_mappings[pin]] |= (0x01 << pin_mappings[pin]);
  } else {
    *port_ddr[port_mappings[pin]] &= ~(0x01 << pin_mappings[pin]);
  }
}

void digital_write(byte pin, byte value) {
  if (value == HIGH) {
    *port[port_mappings[pin]] |= (0x01 << pin_mappings[pin]);
  } else {
    *port[port_mappings[pin]] &= ~(0x01 << pin_mappings[pin]);
  }
}

bool digital_read(byte pin) {
  return (*port_pin[port_mappings[pin]] & (0x01 << pin_mappings[pin]));
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

void analog_write(byte pin, byte value) {
  if (pin > 13) { // pwm pins are D0-D13
    return;
  }

  // enable fast pwm mode
  
}

byte analog_read(byte channel) {
  if (!analog_ready) {
    analog_init();
  }

  // set bit 7 to 1 to enable the ADC
  ADCSRA |= (1 << ADEN);

  // clear the channel selection bits (MUX 5:0)
  ADMUX &= ~(1 << MUX0);
  ADMUX &= ~(1 << MUX1);
  ADMUX &= ~(1 << MUX2);
  ADMUX &= ~(1 << MUX3);
  ADMUX &= ~(1 << MUX4);
  ADCSRB &= ~(1 << MUX5);

  // set the channel selection bits (refer to table 26-4)
  ADMUX |= (0x07 & channel);
  ADCSRB |= (0x08 & channel);

  // set bit 6 of ADCSRA to 1 to start a conversion
  ADCSRA |= (1 << 6);

  // wait for the conversion to complete
  while ((ADCSRA & 0x40) != 0);

  byte val = (byte) ADCH;

  // disable the ADC
  ADCSRA &= ~(1 << ADEN);

  return val;
}