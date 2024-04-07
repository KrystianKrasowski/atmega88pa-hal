#ifndef _LIBAVRHAL_TIMER1_PWM_H
#define _LIBAVRHAL_TIMER1_PWM_H

#include "avrhal/std.h"
#include <stdint.h>

typedef enum
{
    HAL_TIMER1_PWM_FAST_8BIT,
    HAL_TIMER1_PWM_PHASE_CORRECT_8BIT
} hal_timer1_pwm_mode_t;

typedef enum
{
    HAL_TIMER1_PWM_CHANNEL_DISCONNECTED,
    HAL_TIMER1_PWM_CHANNEL_TOGGLE_ON_COMPARE,
    HAL_TIMER1_PWM_CHANNEL_NON_INVERTING,
    HAL_TIMER1_PWM_CHANNEL_INVERTING
} hal_timer1_pwm_channel_mode_t;

typedef struct
{
    hal_timer1_pwm_channel_mode_t mode;
    uint8_t                       duty_cycle;
} hal_timer1_pwm_channel_t;

typedef struct
{
    hal_timer1_pwm_mode_t    mode;
    hal_timer1_pwm_channel_t channel_a;
    hal_timer1_pwm_channel_t channel_b;
    hal_timer_prescaller_t   prescaller;
} hal_timer1_pwm_t;

void
hal_timer1_pwm_init(hal_timer1_pwm_t const *pwm);

void
hal_timer1_pwm_run(hal_timer1_pwm_t const *pwm);

void
hal_timer1_pwm_stop(hal_timer1_pwm_t const *pwm);

#endif