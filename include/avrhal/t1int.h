#ifndef _LIBAVRHAL_T1INT_H
#define _LIBAVRHAL_T1INT_H

#include <stdint.h>

typedef struct
{
    uint8_t timer_overflow   : 1;
    uint8_t output_compare_a : 1;
    uint8_t output_compare_b : 1;
    uint8_t                  : 2;
    uint8_t input_capture    : 1;
    uint8_t                  : 2;
} hal_t1int_t;

void
hal_t1int_init(const hal_t1int_t *t1int);

__attribute__((weak)) void
hal_t1int_input_capture_isr(const uint16_t value);

__attribute__((weak)) void
hal_t1int_output_compare_a_isr(void);

__attribute__((weak)) void
hal_t1int_output_compare_b_isr(void);

__attribute__((weak)) void
hal_t1int_timer_overflow_isr(void);

#endif
