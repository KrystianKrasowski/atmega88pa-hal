#include "avr/io.h"
#include "avr/interrupt.h"
#include "avr/stub.h"
#include "avrhal/t1int.h"
#include <unity.h>

hal_t1int_t interrupts = {
    .input_capture    = 0,
    .output_compare_a = 0,
    .output_compare_b = 0,
    .timer_overflow   = 0,
};

void
setUp(void)
{
}

void
tearDown(void)
{
    cli();
}

void
should_set_input_capture_interrupt(void)
{
    // given
    interrupts.input_capture = 1;

    // when
    hal_t1int_init(&interrupts);

    // then
    TEST_ASSERT_BIT_HIGH(ICIE1, TIMSK1);
    TEST_ASSERT_TRUE(is_global_interrupts_enable());
}

void
should_set_output_compare_a_interrupt(void)
{
    // given
    interrupts.output_compare_a = 1;

    // when
    hal_t1int_init(&interrupts);

    // then
    TEST_ASSERT_BIT_HIGH(OCIE1A, TIMSK1);
    TEST_ASSERT_TRUE(is_global_interrupts_enable());
}

void
should_set_output_compare_b_interrupt(void)
{
    // given
    interrupts.output_compare_b = 1;

    // when
    hal_t1int_init(&interrupts);

    // then
    TEST_ASSERT_BIT_HIGH(OCIE1B, TIMSK1);
    TEST_ASSERT_TRUE(is_global_interrupts_enable());
}

void
should_set_timer_overflow_interrupt(void)
{
    // given
    interrupts.timer_overflow = 1;

    // when
    hal_t1int_init(&interrupts);

    // then
    TEST_ASSERT_BIT_HIGH(TOIE1, TIMSK1);
    TEST_ASSERT_TRUE(is_global_interrupts_enable());
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_set_input_capture_interrupt);
    RUN_TEST(should_set_output_compare_a_interrupt);
    RUN_TEST(should_set_output_compare_b_interrupt);
    RUN_TEST(should_set_timer_overflow_interrupt);
    return UNITY_END();
}