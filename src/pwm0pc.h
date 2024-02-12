#ifndef _LIBAVRHAL_PWM0PC
#define _LIBAVRHAL_PWM0PC

#include <avr/io.h>

typedef enum
{
  HAL_PWM0PC_CHANNEL_DISCONNECTED,
  HAL_PWM0PC_CHANNEL_TOGGLE_ON_COMPARE,
  HAL_PWM0PC_CHANNEL_NON_INVERTING,
  HAL_PWM0PC_CHANNEL_INVERTING
} hal_pwm0pc_channel_mode_t;

typedef struct
{
  hal_pwm0pc_channel_mode_t mode;
  uint8_t duty_cycle;
} hal_pwm0pc_channel_def_t;

typedef enum
{
  HAL_PWM0PC_PRESC_NONE,
  HAL_PWM0PC_PRESC_1,
  HAL_PWM0PC_PRESC_8,
  HAL_PWM0PC_PRESC_64,
  HAL_PWM0PC_PRESC_256,
  HAL_PWM0PC_PRESC_1024,
} hal_pwm0pc_prescaller_t;

typedef struct
{
  hal_pwm0pc_channel_def_t channel_a;
  hal_pwm0pc_channel_def_t channel_b;
  hal_pwm0pc_prescaller_t prescaller;
} hal_pwm0pc_def_t;

void hal_pwm0pc_init(void);
void hal_pwm0pc_run(const hal_pwm0pc_def_t *def);
void hal_pwm0pc_stop(void);

#endif