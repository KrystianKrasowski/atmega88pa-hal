#include "avrhal/timer0.h"
#include <avr/io.h>

void
hal_timer0_run(hal_timer_prescaller_t const prescaller)
{
    switch (prescaller)
    {
        case HAL_TIMER_PRESCALLER_1:
            TCCR0B &= ~((1 << CS02) | (1 << CS01));
            TCCR0B |= (1 << CS00);
            break;
        case HAL_TIMER_PRESCALLER_8:
            TCCR0B &= ~((1 << CS02) | (1 << CS00));
            TCCR0B |= (1 << CS01);
            break;
        case HAL_TIMER_PRESCALLER_64:
            TCCR0B &= ~(1 << CS02);
            TCCR0B |= (1 << CS01) | (1 << CS00);
            break;
        case HAL_TIMER_PRESCALLER_256:
            TCCR0B &= ~((1 << CS01) | (1 << CS00));
            TCCR0B |= (1 << CS02);
            break;
        case HAL_TIMER_PRESCALLER_1024:
            TCCR0B &= ~(1 << CS01);
            TCCR0B |= (1 << CS02) | (1 << CS00);
            break;
        case HAL_TIMER_PRESCALLER_NONE:
        default:
            hal_timer0_stop();
    }
}

void
hal_timer0_set(uint16_t const value)
{
    TCNT0 = value;
}

void
hal_timer0_stop(void)
{
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
}