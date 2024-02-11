#include "pwm0pc.h"

static uint8_t compute_ocrnx(const uint8_t duty_cycle)
{
  return (128 * duty_cycle) / 100;
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

  switch (def->channel_a.mode)
  {
    case HAL_PWM0PC_CHANNEL_NON_INVERTING:
      ctrl_reg_a |= (1 << COM0A1);
      ctrl_reg_a &= ~(1 << COM0A0);
      break;
    case HAL_PWM0PC_CHANNEL_INVERTING:
      ctrl_reg_a |= (1 << COM0A1) | (1 << COM0A0);
      break;
  }

  switch (def->channel_b.mode)
  {
    case HAL_PWM0PC_CHANNEL_DISCONNECTED:
      ctrl_reg_a &= ~((1 << COM0B1) | (1 << COM0B0));
      break;
  }

  switch (presc)
  {
    case HAL_PWM0PC_PRESC_1:
      ctrl_reg_b |= (1 << CS00);
      ctrl_reg_b &= ~((1 << CS02) | (1 << CS01));
      break;
  }

  TCCR0A = ctrl_reg_a;
  TCCR0B = ctrl_reg_b;
  OCR0A = compute_ocrnx(def->channel_a.duty_cycle);
  OCR0B = compute_ocrnx(def->channel_b.duty_cycle);
}

void hal_pwm0pc_stop(void)
{
  uint8_t ctrl_reg_a = TCCR0A;
  ctrl_reg_a &=
      ~((1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0));
  TCCR0A = ctrl_reg_a;
  TCCR0B = 0;
}