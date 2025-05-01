#include "Timer.h"

volatile unsigned uint64_t timer0_overflow_count = 0;
volatile unsigned uint64_t timer0_millis = 0;
volatile unsigned uint8_t timer0_fract = 0;

bool toggle = 1;

ISR(TIMER0_OVF_vect) {
	// copy these to local variables so they can be stored in registers
	// (volatile variables must be read from memory on every access)
	unsigned long m = timer0_millis;
	unsigned char f = timer0_fract;

	m += MILLIS_OVF_INC;
	f += MILLIS_OVF_FRAC_INC;
	if (f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m += 1;
	}

	timer0_fract = f;
	timer0_millis = m;
	timer0_overflow_count++;
}

void setup_timers() {
	// Set TIMER0 64 prescaler
	sbi(TCCR0B, CS01);
	sbi(TCCR0B, CS00);

	// Enable TIMER0 interrupt
	sbi(TIMSK0, TOIE0);
}

uint64_t millis() {

}