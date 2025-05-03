#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <inttypes.h>

// ------------------------------------------------------------------------------------------------------------------------------------------------
// MACRO HELPERS
// ------------------------------------------------------------------------------------------------------------------------------------------------
#define sbi(reg, bit) (reg |= (1 << bit))
#define cbi(reg, bit) (reg &= ~(1 << bit))
#define clockCyclesToMicroseconds(cycles) (cycles / (F_CPU / 1000000L))

// ------------------------------------------------------------------------------------------------------------------------------------------------
// GENERAL DEFINITIONS
// ------------------------------------------------------------------------------------------------------------------------------------------------
#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#define LOW 0x0
#define HIGH 0x1
#define NUM_PINS 70
#define NUM_PWM_PINS 14
#define NUM_PORTS 11
#define F_CPU 16000000L

// ------------------------------------------------------------------------------------------------------------------------------------------------
// Digital pin registers and constants
// ------------------------------------------------------------------------------------------------------------------------------------------------
// Port character to array index mappings
#define PORTA_INDEX 0
#define PORTB_INDEX 1
#define PORTC_INDEX 2
#define PORTD_INDEX 3
#define PORTE_INDEX 4
#define PORTF_INDEX 5
#define PORTG_INDEX 6
#define PORTH_INDEX 7
#define PORTJ_INDEX 8
#define PORTK_INDEX 9
#define PORTL_INDEX 10

static const uint8_t port_mappings[NUM_PINS] = {
  PORTE_INDEX, PORTE_INDEX, PORTE_INDEX, PORTE_INDEX, PORTG_INDEX, PORTE_INDEX, PORTH_INDEX, PORTH_INDEX, PORTH_INDEX, PORTH_INDEX,
  PORTB_INDEX, PORTB_INDEX, PORTB_INDEX, PORTB_INDEX, PORTJ_INDEX, PORTJ_INDEX, PORTH_INDEX, PORTH_INDEX, PORTD_INDEX, PORTD_INDEX, 
  PORTD_INDEX, PORTD_INDEX, PORTA_INDEX, PORTA_INDEX, PORTA_INDEX, PORTA_INDEX, PORTA_INDEX, PORTA_INDEX, PORTA_INDEX, PORTA_INDEX, 
  PORTC_INDEX, PORTC_INDEX, PORTC_INDEX, PORTC_INDEX, PORTC_INDEX, PORTC_INDEX, PORTC_INDEX, PORTC_INDEX, PORTD_INDEX, PORTG_INDEX, 
  PORTG_INDEX, PORTG_INDEX, PORTL_INDEX, PORTL_INDEX, PORTL_INDEX, PORTL_INDEX, PORTL_INDEX, PORTL_INDEX, PORTL_INDEX, PORTL_INDEX, 
  PORTB_INDEX, PORTB_INDEX, PORTB_INDEX, PORTB_INDEX, PORTF_INDEX, PORTF_INDEX, PORTF_INDEX, PORTF_INDEX, PORTF_INDEX, PORTF_INDEX, 
  PORTF_INDEX, PORTF_INDEX, PORTK_INDEX, PORTK_INDEX, PORTK_INDEX, PORTK_INDEX, PORTK_INDEX, PORTK_INDEX, PORTK_INDEX, PORTK_INDEX
};
static const uint8_t pin_mappings[NUM_PINS] = {
  0, 1, 4, 5, 5, 3, 3, 4, 5, 6, 4, 5, 6, 7, 1, 0, 1, 0, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 0, 7, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7
}; 

static volatile unsigned char *port[NUM_PORTS] = {0x22, 0x25, 0x28, 0x2B, 0x2E, 0x31, 0x34, 0x102, 0x105, 0x108, 0x10B};
static volatile unsigned char *port_ddr[NUM_PORTS] = {0x21, 0x24, 0x27, 0x2A, 0x2D, 0x30, 0x33, 0x101, 0x104, 0x107, 0x10A};
static volatile unsigned char *port_pin[NUM_PORTS] = {0x20, 0x23, 0x26, 0x29, 0x2C, 0x2F, 0x32, 0x100, 0x103, 0x106, 0x109};

// Analog pin registers

#endif