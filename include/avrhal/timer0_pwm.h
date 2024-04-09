#ifndef _LIBAVRHAL_TIMER0_PWM_H
#define _LIBAVRHAL_TIMER0_PWM_H

#include "avrhal/gpio.h"
#include "avrhal/std.h"
#include <stdint.h>

#define HAL_GPIO_OC0A HAL_GPIO_PD6
#define HAL_GPIO_OC0B HAL_GPIO_PD5

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
    hal_timer_prescaller_t   prescaller;
} hal_timer0_pwm_t;

void
hal_timer0_pwm_init(hal_timer0_pwm_t const *pwm);

void
hal_timer0_pwm_run(hal_timer0_pwm_t const *pwm);

void
hal_timer0_pwm_stop(hal_timer0_pwm_t const *pwm);

#endif