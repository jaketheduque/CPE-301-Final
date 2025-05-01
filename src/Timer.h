/**
* Much of this code is copied from the Arduino library, specifically from "wiring.c", just
* specifically tailored for the ATmega2560 chip
*/

#ifndef TIMER_H
#define TIMER_H

#include <avr/interrupt.h>

#include "MyArduino.h"
#include "GPIO.h"

// Prescaler set to 64, and 8-bit timer, so overflow occurs every 64*256 clock cycles
#define MICROSECONDS_PER_TIMER0_OVF clockCyclesToMicroseconds(64 * 256)
// how many milliseconds pass per TIMER0 overflow
#define MILLIS_OVF_INC (MICROSECONDS_PER_TIMER0_OVF / 1000)
// how many fractional milliseconds pass per TIMER0 overflow
#define MILLIS_OVF_FRAC_INC ((MICROSECONDS_PER_TIMER0_OVF % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)

extern volatile unsigned uint64_t timer0_overflow_count;
extern volatile unsigned uint64_t timer0_millis;
extern volatile unsigned uint8_t timer0_fract;

void setup_timers();
uint64_t millis();

#endif