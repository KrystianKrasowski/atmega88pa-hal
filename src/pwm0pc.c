#include "pwm0pc.h"

static uint8_t compute_ocrnx(const uint8_t duty_cycle)
{
  return (128 * duty_cycle) / 100;
}

static void apply_com0nx(hal_pwm0pc_channel_mode_t channel_mode,
                         uint8_t *ctrl_reg_a,
                         uint8_t *com0n1_bit,
                         uint8_t *com0n0_bit)
{
  switch (channel_mode)
  {
    case HAL_PWM0PC_CHANNEL_NON_INVERTING:
      *ctrl_reg_a |= (1 << *com0n1_bit);
      *ctrl_reg_a &= ~(1 << *com0n0_bit);
      break;
    case HAL_PWM0PC_CHANNEL_INVERTING:
      *ctrl_reg_a |= (1 << *com0n1_bit) | (1 << *com0n0_bit);
      break;
    case HAL_PWM0PC_CHANNEL_DISCONNECTED:
    default:
      *ctrl_reg_a &= ~((1 << *com0n1_bit) | (1 << *com0n0_bit));
      break;
  }
}

static void apply_prescaler(hal_pwm0pc_prescaller_t mode, uint8_t *ctrl_reg_b)
{
  switch (mode) {
    case HAL_PWM0PC_PRESC_1:
      *ctrl_reg_b |= (1 << CS00);
      *ctrl_reg_b &= ~((1 << CS02) | (1 << CS01));
      break;
  }
}

void hal_pwm0pc_init(void)
{
  uint8_t ctrl_reg_a = TCCR0A;
  uint8_t ctrl_reg_b = TCCR0B;
  ctrl_reg_a |= (1 << WGM00);
  ctrl_reg_a &= ~(1 << WGM01);
  ctrl_reg_b &= ~(1 << WGM02);
  TCCR0A = ctrl_reg_a;
  TCCR0B = ctrl_reg_b;
}

void hal_pwm0pc_run(const hal_pwm0pc_def_t *def,
                    const hal_pwm0pc_prescaller_t presc)
{
  uint8_t ctrl_reg_a = TCCR0A;
  uint8_t ctrl_reg_b = TCCR0B;
  apply_com0nx(def->channel_a.mode, &ctrl_reg_a, &COM0A1, &COM0A0);
  apply_com0nx(def->channel_b.mode, &ctrl_reg_a, &COM0B1, &COM0B0);
  apply_prescaler(presc, &ctrl_reg_b);
  TCCR0A = ctrl_reg_a;
  TCCR0B = ctrl_reg_b;
  OCR0A = compute_ocrnx(def->channel_a.duty_cycle);
  OCR0B = compute_ocrnx(def->channel_b.duty_cycle);
}

void hal_pwm0pc_stop(void)
{
  uint8_t ctrl_reg_a = TCCR0A;
  apply_com0nx(HAL_PWM0PC_CHANNEL_DISCONNECTED, &ctrl_reg_a, &COM0A1, &COM0A0);
  apply_com0nx(HAL_PWM0PC_CHANNEL_DISCONNECTED, &ctrl_reg_a, &COM0B1, &COM0B0);
  TCCR0A = ctrl_reg_a;
  TCCR0B = 0;
}