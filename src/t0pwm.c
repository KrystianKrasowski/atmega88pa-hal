#include <avr/io.h>
#include "t0pwm.h"

static uint8_t compute_ocrnx(uint8_t duty_cycle)
{
  if (duty_cycle > 100)
  {
    duty_cycle = 100;
  }

  return (255 * duty_cycle) / 100;
}

static void apply_com0nx(hal_t0pwm_channel_mode_t channel_mode,
                         uint8_t com0n1_bit,
                         uint8_t com0n0_bit)
{
  switch (channel_mode)
  {
    case HAL_T0PWM_CHANNEL_NON_INVERTING:
      TCCR0A |= (1 << com0n1_bit);
      TCCR0A &= ~(1 << com0n0_bit);
      break;
    case HAL_T0PWM_CHANNEL_INVERTING:
      TCCR0A |= (1 << com0n1_bit) | (1 << com0n0_bit);
      break;
    // According to atmega88pa datasheet, channel B has no compare match mode,
    // thus this HAL use case falls back to disconnected mode on channel B
    case HAL_T0PWM_CHANNEL_TOGGLE_ON_COMPARE:
      if (com0n1_bit == COM0B1 && com0n0_bit == COM0B0)
      {
        TCCR0A &= ~((1 << com0n1_bit) | (1 << com0n0_bit));
      }
      else
      {
        TCCR0A &= ~(1 << com0n1_bit);
        TCCR0A |= (1 << com0n0_bit);
      }
      break;
    case HAL_T0PWM_CHANNEL_DISCONNECTED:
    default:
      TCCR0A &= ~((1 << com0n1_bit) | (1 << com0n0_bit));
      break;
  }
}

static void apply_prescaler(hal_timer_prescaller_t mode)
{
  switch (mode)
  {
    case HAL_TIMER_PRESCALLER_1:
      TCCR0B |= (1 << CS00);
      TCCR0B &= ~((1 << CS02) | (1 << CS01));
      break;
    case HAL_TIMER_PRESCALLER_8:
      TCCR0B |= (1 << CS01);
      TCCR0B &= ~((1 << CS02) | (1 << CS00));
      break;
    case HAL_TIMER_PRESCALLER_64:
      TCCR0B |= (1 << CS01) | (1 << CS00);
      TCCR0B &= ~(1 << CS02);
      break;
    case HAL_TIMER_PRESCALLER_256:
      TCCR0B |= (1 << CS02);
      TCCR0B &= ~((1 << CS01) | (1 << CS00));
      break;
    case HAL_TIMER_PRESCALLER_1024:
      TCCR0B |= (1 << CS02) | (1 << CS00);
      TCCR0B &= ~(1 << CS01);
      break;
    default:
      TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
  }
}

void hal_t0pwm_init(const hal_t0pwm_def_t *def)
{
  switch (def->mode)
  {
    case HAL_T0PWM_MODE_PHASE_CORRECT:
      TCCR0A |= (1 << WGM00);
      TCCR0A &= ~(1 << WGM01);
      TCCR0B &= ~(1 << WGM02);
      break;
    case HAL_T0PWM_MODE_FAST:
    default:
      TCCR0A |= (1 << WGM01) | (1 << WGM00);
      TCCR0B &= ~(1 << WGM02);
  }
}

void hal_t0pwm_run(const hal_t0pwm_def_t *def)
{
  apply_com0nx(def->channel_a.mode, COM0A1, COM0A0);
  apply_com0nx(def->channel_b.mode, COM0B1, COM0B0);
  apply_prescaler(def->prescaller);
  OCR0A = compute_ocrnx(def->channel_a.duty_cycle);
  OCR0B = compute_ocrnx(def->channel_b.duty_cycle);
}

void hal_t0pwm_stop(void)
{
  apply_com0nx(HAL_T0PWM_CHANNEL_DISCONNECTED, COM0A1, COM0A0);
  apply_com0nx(HAL_T0PWM_CHANNEL_DISCONNECTED, COM0B1, COM0B0);
  TCCR0B = 0;
}
