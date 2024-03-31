#ifndef _LIBAVRHAL_TIMER0_H
#define _LIBAVRHAL_TIMER0_H

#include "std.h"
#include <stdint.h>

void
hal_timer0_run(hal_timer_prescaller_t presc);

void
hal_timer0_set(uint16_t value);

void
hal_timer0_stop(void);

#endif