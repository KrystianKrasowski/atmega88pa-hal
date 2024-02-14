#include "t1int.h"

void hal_t1int_set(const uint8_t mask)
{
  TIMSK1 = mask;
  sei();
}

__attribute__((weak)) void hal_t1int_on_input_capture(const uint16_t value) {}

ISR(TIMER1_CAPT_vect) { hal_t1int_on_input_capture(ICR1); }