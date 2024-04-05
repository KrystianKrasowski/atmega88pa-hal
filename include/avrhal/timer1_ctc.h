#ifndef _LIBAVRHAL_TIMER1_CTC_H
#define _LIBAVRHAL_TIMER1_CTC_H

#include <stdint.h>

typedef struct
{
    /**
     * @brief In CTC mode the timer counts up to OCR1A value
     *
     */
    uint16_t resolution;

    /**
     * @brief A resolution for channel B. Note it shouldt be greater than
     * resolution
     *
     */
    uint16_t output_compare_b;
} hal_timer1_ctc_t;

/**
 * @brief Initializes timer1 in CTC mode
 *
 * A CTC mode is "Clear Timer on Compare match"
 * 
 * @param timer 
 */
void
hal_timer1_ctc_init(hal_timer1_ctc_t const *timer);

#endif