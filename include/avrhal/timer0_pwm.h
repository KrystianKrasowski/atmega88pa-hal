#ifndef _LIBAVRHAL_TIMER0_PWM_H
#define _LIBAVRHAL_TIMER0_PWM_H

#include <stdint.h>

typedef enum
{
    HAL_TIMER0_PWM_FAST,
    HAL_TIMER0_PWM_PHASE_CORRECT
} hal_timer0_pwm_mode_t;

typedef enum
{
    HAL_TIMER0_PWM_CHANNEL_DISCONNECTED,
    HAL_TIMER0_PWM_CHANNEL_TOGGLE_ON_COMPARE,
    HAL_TIMER0_PWM_CHANNEL_NON_INVERTING,
    HAL_TIMER0_PWM_CHANNEL_INVERTING
} hal_timer0_pwm_channel_mode_t;

typedef struct
{
    hal_timer0_pwm_channel_mode_t mode;
    uint8_t                       duty_cycle;
} hal_timer0_pwm_channel_t;

typedef struct
{
    hal_timer0_pwm_mode_t    mode;
    hal_timer0_pwm_channel_t channel_a;
    hal_timer0_pwm_channel_t channel_b;
} hal_timer0_pwm_t;

void
hal_timer0_pwm_init(const hal_timer0_pwm_t *pwm);

#endif