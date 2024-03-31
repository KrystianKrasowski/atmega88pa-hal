#include "avr/io.h"
#include "avrhal/t1ctc.h"
#include <unity.h>

hal_t1ctc_t timer = {
    .prescaller       = HAL_TIMER_PRESCALLER_1,
    .resolution       = 0,
    .output_compare_b = 0,
};

void
setUp(void)
{
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A  = 0;
    OCR1B  = 0;
}

void
tearDown(void)
{
}

void
should_unset_prescaller(void)
{
    // when
    hal_t1ctc_stop();

    // then
    TEST_ASSERT_BIT_LOW(CS12, TCCR1B);
    TEST_ASSERT_BIT_LOW(CS11, TCCR1B);
    TEST_ASSERT_BIT_LOW(CS10, TCCR1B);
}

int
main(void)
{
    UNITY_BEGIN();
    return UNITY_END();
}