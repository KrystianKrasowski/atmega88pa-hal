#ifndef _LIBAVRHAL_T1CTC_H
#define _LIBAVRHAL_T1CTC_H

#include "std.h"
#include <stdint.h>

typedef struct
{
    hal_timer_prescaller_t prescaller;
    uint16_t               resolution;
    uint16_t               output_compare_b;
} hal_t1ctc_t;

void
hal_t1ctc_init(const hal_t1ctc_t *t1ctc);

void
hal_t1ctc_run(const hal_t1ctc_t *t1ctc);

void
hal_t1ctc_stop(void);

#endif
