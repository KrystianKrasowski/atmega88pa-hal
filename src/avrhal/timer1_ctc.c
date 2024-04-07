#include "avrhal/timer1_ctc.h"
#include <avr/io.h>

void
hal_timer1_ctc_init(hal_timer1_ctc_t const *timer)
{
    TCCR1A = 0;
    TCCR1B |= (1 << WGM12);
    OCR1A = timer->resolution;
    OCR1B = timer->output_compare_b;
}