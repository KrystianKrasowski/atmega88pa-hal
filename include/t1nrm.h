#ifndef _LIBAVRHAL_T1NRM
#define _LIBAVRHAL_T1NRM

#include "std.h"
#include <stdint.h>

void
hal_t1nrm_run(hal_timer_prescaller_t presc);

void
hal_t1nrm_set(uint16_t value);

void
hal_t1nrm_stop(void);

#endif
