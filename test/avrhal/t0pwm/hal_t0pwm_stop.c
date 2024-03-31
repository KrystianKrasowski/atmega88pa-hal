#include "avr/io.h"
#include "avrhal/t0pwm.h"
#include "helpers.h"
#include "unity_config.h"
#include <unity.h>

void
setUp(void)
{
}

void
tearDown(void)
{
}

void
should_disconnect_channels(void)
{
    // when
    hal_t0pwm_stop();

    // then
    TEST_ASSERT_BIT_LOW(COM0A1, TCCR0A);
    TEST_ASSERT_BIT_LOW(COM0A0, TCCR0A);
    TEST_ASSERT_BIT_LOW(COM0B1, TCCR0B);
    TEST_ASSERT_BIT_LOW(COM0B0, TCCR0B);
}

void
should_unset_prescaller(void)
{
    // when
    hal_t0pwm_stop();

    // then
    TEST_ASSERT_BIT_LOW(CS02, TCCR0B);
    TEST_ASSERT_BIT_LOW(CS01, TCCR0B);
    TEST_ASSERT_BIT_LOW(CS00, TCCR0B);
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_disconnect_channels);
    RUN_TEST(should_unset_prescaller);
    return UNITY_END();
}