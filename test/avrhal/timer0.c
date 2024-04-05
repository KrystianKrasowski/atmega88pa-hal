#include "avr/io.h"
#include "avrhal/timer0.h"
#include "helpers.h"
#include "unity_config.h"
#include <unity.h>

void
setUp(void)
{
    TCCR0B = 0;
}

void
tearDown(void)
{
}

void
should_run_prescaller(hal_timer_prescaller_t prescaller,
                      uint8_t                cs02,
                      uint8_t                cs01,
                      uint8_t                cs00)
{
    // when
    hal_timer0_run(prescaller);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(CS02, cs02, TCCR0B, "Unexpected CS02");
    TEST_ASSERT_BIT_STATE_MESSAGE(CS01, cs01, TCCR0B, "Unexpected CS01");
    TEST_ASSERT_BIT_STATE_MESSAGE(CS00, cs00, TCCR0B, "Unexpected CS00");
}

int
main()
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_run_prescaller,
                   HAL_TIMER_PRESCALLER_1,
                   ~BIT(CS02),
                   ~BIT(CS01),
                   BIT(CS00));

    RUN_PARAM_TEST(should_run_prescaller,
                   HAL_TIMER_PRESCALLER_8,
                   ~BIT(CS02),
                   BIT(CS01),
                   ~BIT(CS00));

    RUN_PARAM_TEST(should_run_prescaller,
                   HAL_TIMER_PRESCALLER_64,
                   ~BIT(CS02),
                   BIT(CS01),
                   BIT(CS00));

    RUN_PARAM_TEST(should_run_prescaller,
                   HAL_TIMER_PRESCALLER_256,
                   BIT(CS02),
                   ~BIT(CS01),
                   ~BIT(CS00));

    RUN_PARAM_TEST(should_run_prescaller,
                   HAL_TIMER_PRESCALLER_1024,
                   BIT(CS02),
                   ~BIT(CS01),
                   BIT(CS00));

    return UNITY_END();
}