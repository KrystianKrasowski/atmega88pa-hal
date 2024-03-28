#ifndef _LIBAVRHAL_T0PWM_H
#define _LIBAVRHAL_T0PWM_H

#include "std.h"
#include <stdint.h>

typedef enum
{
    HAL_T0PWM_MODE_FAST,
    HAL_T0PWM_MODE_PHASE_CORRECT
} hal_t0pwm_mode_t;

typedef enum
{
    HAL_T0PWM_CHANNEL_DISCONNECTED,
    HAL_T0PWM_CHANNEL_TOGGLE_ON_COMPARE,
    HAL_T0PWM_CHANNEL_NON_INVERTING,
    HAL_T0PWM_CHANNEL_INVERTING
} hal_t0pwm_channel_mode_t;

typedef struct
{
    hal_t0pwm_channel_mode_t mode;
    uint8_t                  duty_cycle;
} hal_t0pwm_channel_def_t;

typedef struct
{
    hal_t0pwm_mode_t        mode;
    hal_t0pwm_channel_def_t channel_a;
    hal_t0pwm_channel_def_t channel_b;
    hal_timer_prescaller_t  prescaller;
} hal_t0pwm_t;

void
hal_t0pwm_init(const hal_t0pwm_t *t0pwm);

void
hal_t0pwm_run(const hal_t0pwm_t *t0pwm);

void
hal_t0pwm_stop(void);

#endif
