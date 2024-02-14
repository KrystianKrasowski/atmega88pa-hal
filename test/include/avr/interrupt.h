#include <stdint.h>

#ifndef _AVR_INTERRUPT_MOCK
#define _AVR_INTERRUPT_MOCK

#define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)

#endif