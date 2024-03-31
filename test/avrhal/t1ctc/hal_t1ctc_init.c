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
should_set_wgm(void)
{
    // when
    hal_t1ctc_init(&timer);

    // then
    TEST_ASSERT_BIT_HIGH(WGM12, TCCR1B);
}

void
should_set_resolution(void)
{
    // given
    timer.resolution = 0x7f;

    // when
    hal_t1ctc_init(&timer);

    // then
    TEST_ASSERT_EQUAL(0x7f, OCR1A);
}

void
should_set_output_compare_for_b_channel(void)
{
    // given
    timer.output_compare_b = 0x7f;

    // when
    hal_t1ctc_init(&timer);

    // then
    TEST_ASSERT_EQUAL(0x7f, OCR1B);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_set_wgm);
    RUN_TEST(should_set_resolution);
    RUN_TEST(should_set_output_compare_for_b_channel);
    return UNITY_END();
}