#ifndef _LIBAVRHAL_T1NRM_H
#error "Include <avrhal/t1nrm.h> instead of this file."
#endif

#ifndef _LIBAVRHAL_T1NRM_VX_H
#define _LIBAVRHAL_T1NRM_VX_H 1

#include "std.h"
#include <stdint.h>

void
hal_t1nrm_run(hal_timer_prescaller_t presc);

void
hal_t1nrm_set(uint16_t value);

void
hal_t1nrm_stop(void);

#endif
