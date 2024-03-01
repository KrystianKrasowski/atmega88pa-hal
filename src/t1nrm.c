#include <avr/io.h>
#include "t1nrm.h"

// TODO: Noise canceller for input capture
// TODO: Input capture edge select

void hal_t1nrm_run(hal_timer_prescaller_t presc)
{
  switch (presc)
  {
    case HAL_TIMER_PRESCALLER_1:
      TCCR1B &= ~((1 << CS12) | (1 << CS11));
      TCCR1B |= (1 << CS10);
      break;
    case HAL_TIMER_PRESCALLER_8:
      TCCR1B &= ~((1 << CS12) | (1 << CS10));
      TCCR1B |= (1 << CS11);
      break;
    case HAL_TIMER_PRESCALLER_64:
      TCCR1B &= ~(1 << CS12);
      TCCR1B |= (1 << CS11) | (1 << CS10);
      break;
    case HAL_TIMER_PRESCALLER_256:
      TCCR1B &= ~((1 << CS11) | (1 << CS10));
      TCCR1B |= (1 << CS12);
      break;
    case HAL_TIMER_PRESCALLER_1024:
      TCCR1B &= ~(1 << CS11);
      TCCR1B |= (1 << CS12) | (1 << CS10);
      break;
  case HAL_TIMER_PRESCALLER_NONE:
    default:
      hal_t1nrm_stop();
  }
}

void hal_t1nrm_set(uint16_t value)
{
  TCNT1 = value;
}

void hal_t1nrm_stop(void)
{
  TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}
