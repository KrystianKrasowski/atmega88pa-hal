#ifndef _LIBAVRHAL_T1CTC
#define _LIBAVRHAL_T1CTC

#include "std.h"
#include <stdint.h>

typedef struct
{
  hal_timer_prescaller_t prescaller;
} hal_t1ctc_def_t;

void hal_t1ctc_init(const hal_t1ctc_def_t *def);
void hal_t1ctc_run(const hal_t1ctc_def_t *def);
void hal_t1ctc_stop(void);

void example(void);

#endif
