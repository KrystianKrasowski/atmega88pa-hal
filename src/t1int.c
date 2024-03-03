#include "t1int.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void hal_t1int_configure(const hal_t1int_cfg_t *cfg)
{
  TIMSK1 = *(uint8_t *)cfg;
  sei();
}

__attribute__((weak)) void hal_t1int_on_input_capture(const uint16_t value) {}

__attribute__((weak)) void hal_t1int_on_output_compare_a(void) {}

__attribute__((weak)) void hal_t1int_on_output_compare_b(void) {}

__attribute__((weak)) void hal_t1int_on_timer_overflow(void) {}

ISR(TIMER1_CAPT_vect) { hal_t1int_on_input_capture(ICR1); }
ISR(TIMER1_COMPA_vect) { hal_t1int_on_output_compare_a(); }
ISR(TIMER1_COMPB_vect) { hal_t1int_on_output_compare_b(); }
ISR(TIMER1_OVF_vect) { hal_t1int_on_timer_overflow(); }
