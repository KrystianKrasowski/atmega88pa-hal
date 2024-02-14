#include "t1nrm.h"

// TODO: Noise canceller for input capture
// TODO: Input capture edge select

void hal_t1nrm_run(hal_t1nrm_prescaller_t presc)
{
  switch (presc)
  {
    case HAL_T1NRM_PRESC_1:
      TCCR1B &= ~((1 << CS12) | (1 << CS11));
      TCCR1B |= (1 << CS10);
      break;
    case HAL_T1NRM_PRESC_8:
      TCCR1B &= ~((1 << CS12) | (1 << CS10));
      TCCR1B |= (1 << CS11);
      break;
    case HAL_T1NRM_PRESC_64:
      TCCR1B &= ~(1 << CS12);
      TCCR1B |= (1 << CS11) | (1 << CS10);
      break;
    case HAL_T1NRM_PRESC_256:
      TCCR1B &= ~((1 << CS11) | (1 << CS10));
      TCCR1B |= (1 << CS12);
      break;
    case HAL_T1NRM_PRESC_1024:
      TCCR1B &= ~(1 << CS11);
      TCCR1B |= (1 << CS12) | (1 << CS10);
      break;
    case HAL_T1NRM_PRESC_NONE:
    default:
      hal_t1nrm_stop();
  }
}

void hal_t1nrm_stop(void)
{
  TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}