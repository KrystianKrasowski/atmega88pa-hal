#include "avrhal/t1ctc.h"
#include <avr/io.h>

void
hal_t1ctc_init(const hal_t1ctc_def_t *def)
{
    TCCR1A = 0;
    TCCR1B |= (1 << WGM12);
    OCR1A = def->resolution;
    OCR1B = def->output_compare_b;
}

void
hal_t1ctc_run(const hal_t1ctc_def_t *def)
{
    switch (def->prescaller)
    {
        case HAL_TIMER_PRESCALLER_1:
            TCCR1B &= ~((1 << CS12) | (1 << CS11));
            TCCR1B |= (1 << CS10);
            break;
        case HAL_TIMER_PRESCALLER_8:
            TCCR1B &= ~((1 << CS12) | (1 << CS10));
            TCCR1B |= (1 << CS11);
            break;
        case HAL_TIMER_PRESCALLER_64:
            TCCR1B &= ~(1 << CS12);
            TCCR1B |= (1 << CS11) | (1 << CS10);
            break;
        case HAL_TIMER_PRESCALLER_256:
            TCCR1B &= ~((1 << CS11) | (1 << CS10));
            TCCR1B |= (1 << CS12);
            break;
        case HAL_TIMER_PRESCALLER_1024:
            TCCR1B &= ~(1 << CS11);
            TCCR1B |= (1 << CS12) | (1 << CS10);
            break;
        default:
            TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
    }
}
