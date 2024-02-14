#ifndef _LIBAVRHAL_T1INT
#define _LIBAVRHAL_T1INT

#include <avr/io.h>
#include <avr/interrupt.h>

#define HAL_T1INT_CFG_TIMER_OVERFLOW TOIE1
#define HAL_T1INT_CFG_OUTPUT_COMPARE_A OCIE1A
#define HAL_T1INT_CFG_OUTPUT_COMPARE_B OCIE1B
#define HAL_T1INT_CFG_INPUT_CAPTURE ICIE1

void hal_t1int_set(const uint8_t mask);
void t1int_on_input_capture(const uint16_t value);

#endif