#include "t1int.h"

void hal_t1int_configure(const hal_t1int_cfg_t *cfg)
{
  TIMSK1 = *(uint8_t *)cfg;
  sei();
}

void hal_t1int_on_input_capture(const uint16_t value) {}

ISR(TIMER1_CAPT_vect) { hal_t1int_on_input_capture(ICR1); }