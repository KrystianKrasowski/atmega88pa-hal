#include "t1nrm.h"

#include "unity_config.h"
#include <unity/unity.h>

uint8_t  TCCR1A = 0;
uint8_t  TCCR1B = 0;
uint8_t  TCCR1C = 0;
uint16_t TCNT1  = 0;
uint8_t  CS12   = 2;
uint8_t  CS11   = 1;
uint8_t  CS10   = 0;

void
should_run_with_prescaler(hal_timer_prescaller_t presc, uint8_t expected_bits)
{
    // when
    hal_t1nrm_run(presc);

    // then
    TEST_ASSERT_BITS(0x0f, expected_bits, TCCR1B);
}

void
should_stop(void)
{
    // when
    hal_t1nrm_stop();

    // then
    TEST_ASSERT_BITS(0x0f, 0x00, TCCR1B);
}

void
setUp()
{
}

void
tearDown()
{
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_run_with_prescaler, HAL_TIMER_PRESCALLER_1, 0x01);
    RUN_TEST(should_run_with_prescaler, HAL_TIMER_PRESCALLER_8, 0x02);
    RUN_TEST(should_run_with_prescaler, HAL_TIMER_PRESCALLER_64, 0x03);
    RUN_TEST(should_run_with_prescaler, HAL_TIMER_PRESCALLER_256, 0x04);
    RUN_TEST(should_run_with_prescaler, HAL_TIMER_PRESCALLER_1024, 0x05);
    RUN_TEST(should_run_with_prescaler, HAL_TIMER_PRESCALLER_NONE, 0x00);
    RUN_TEST(should_stop);
    return UNITY_END();
}
