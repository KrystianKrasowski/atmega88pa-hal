#include <avr/io.h>
#include <avr/interrupt.h>
#include "t1int.h"

void hal_t1int_configure(const hal_t1int_cfg_t *cfg)
{
  TIMSK1 = *(uint8_t *)cfg;
  sei();
}

void hal_t1int_on_input_capture(const uint16_t value) {}

void hal_t1int_on_output_compare_a(void) {}

void hal_t1int_on_timer_overflow(void) {}

ISR(TIMER1_CAPT_vect) { hal_t1int_on_input_capture(ICR1); }
ISR(TIMER1_COMPA_vect) { hal_t1int_on_output_compare_a(); }
ISR(TIMER1_OVF_vect) { hal_t1int_on_timer_overflow(); }
