#include "avrhal/t1int.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void
hal_t1int_init(const hal_t1int_t *t1int)
{
    TIMSK1 = *(uint8_t *)t1int;
    sei();
}

__attribute__((weak)) void
hal_t1int_input_capture_isr(const uint16_t value)
{
}

__attribute__((weak)) void
hal_t1int_output_compare_a_isr(void)
{
}

__attribute__((weak)) void
hal_t1int_output_compare_b_isr(void)
{
}

__attribute__((weak)) void
hal_t1int_timer_overflow_isr(void)
{
}

ISR(TIMER1_CAPT_vect)
{
    hal_t1int_input_capture_isr(ICR1);
}
ISR(TIMER1_COMPA_vect)
{
    hal_t1int_output_compare_a_isr();
}
ISR(TIMER1_COMPB_vect)
{
    hal_t1int_output_compare_b_isr();
}
ISR(TIMER1_OVF_vect)
{
    hal_t1int_timer_overflow_isr();
}
