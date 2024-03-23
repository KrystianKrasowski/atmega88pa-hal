#ifndef _LIBAVRHAL_STD_H
#define _LIBAVRHAL_STD_H

typedef enum
{
    HAL_TIMER_PRESCALLER_NONE,
    HAL_TIMER_PRESCALLER_1,
    HAL_TIMER_PRESCALLER_8,
    HAL_TIMER_PRESCALLER_64,
    HAL_TIMER_PRESCALLER_256,
    HAL_TIMER_PRESCALLER_1024,
} hal_timer_prescaller_t;

#endif