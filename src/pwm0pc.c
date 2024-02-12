#include "pwm0pc.h"

static uint8_t compute_ocrnx(uint8_t duty_cycle)
{
  if (duty_cycle > 100) {
    duty_cycle = 100;
  }

  return (128 * duty_cycle) / 100;
}

static void apply_com0nx(hal_pwm0pc_channel_mode_t channel_mode,
                         uint8_t com0n1_bit,
                         uint8_t com0n0_bit)
{
  switch (channel_mode)
  {
    case HAL_PWM0PC_CHANNEL_NON_INVERTING:
      TCCR0A |= (1 << com0n1_bit);
      TCCR0A &= ~(1 << com0n0_bit);
      break;
    case HAL_PWM0PC_CHANNEL_INVERTING:
      TCCR0A |= (1 << com0n1_bit) | (1 << com0n0_bit);
      break;
    // According to atmega88pa datasheet, channel B has no compare match mode,
    // thus this HAL use case falls back to disconnected mode on channel B
    case HAL_PWM0PC_CHANNEL_TOGGLE_ON_COMPARE:
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
    case HAL_PWM0PC_CHANNEL_DISCONNECTED:
    default:
      TCCR0A &= ~((1 << com0n1_bit) | (1 << com0n0_bit));
      break;
  }
}

static void apply_prescaler(hal_pwm0pc_prescaller_t mode)
{
  switch (mode)
  {
    case HAL_PWM0PC_PRESC_1:
      TCCR0B |= (1 << CS00);
      TCCR0B &= ~((1 << CS02) | (1 << CS01));
      break;
    case HAL_PWM0PC_PRESC_8:
      TCCR0B |= (1 << CS01);
      TCCR0B &= ~((1 << CS02) | (1 << CS00));
      break;
    case HAL_PWM0PC_PRESC_64:
      TCCR0B |= (1 << CS01) | (1 << CS00);
      TCCR0B &= ~(1 << CS02);
      break;
    case HAL_PWM0PC_PRESC_256:
      TCCR0B |= (1 << CS02);
      TCCR0B &= ~((1 << CS01) | (1 << CS00));
      break;
    case HAL_PWM0PC_PRESC_1024:
      TCCR0B |= (1 << CS02) | (1 << CS00);
      TCCR0B &= ~(1 << CS01);
      break;
    default:
      TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
  }
}

void hal_pwm0pc_init(void)
{
  TCCR0A |= (1 << WGM00);
  TCCR0A &= ~(1 << WGM01);
  TCCR0B &= ~(1 << WGM02);
}

void hal_pwm0pc_run(const hal_pwm0pc_def_t *def)
{
  apply_com0nx(def->channel_a.mode, COM0A1, COM0A0);
  apply_com0nx(def->channel_b.mode, COM0B1, COM0B0);
  apply_prescaler(def->prescaller);
  OCR0A = compute_ocrnx(def->channel_a.duty_cycle);
  OCR0B = compute_ocrnx(def->channel_b.duty_cycle);
}

void hal_pwm0pc_stop(void)
{
  apply_com0nx(HAL_PWM0PC_CHANNEL_DISCONNECTED, COM0A1, COM0A0);
  apply_com0nx(HAL_PWM0PC_CHANNEL_DISCONNECTED, COM0B1, COM0B0);
  TCCR0B = 0;
}