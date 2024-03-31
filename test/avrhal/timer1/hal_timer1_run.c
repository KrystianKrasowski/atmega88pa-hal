#include "avr/io.h"
#include "avrhal/timer1.h"
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
should_set_prescaller(hal_timer_prescaller_t prescaller,
                      uint8_t                cs12,
                      uint8_t                cs11,
                      uint8_t                cs10)
{
    // when
    hal_timer1_run(prescaller);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(CS12, cs12, TCCR1B, "Unexpected CS12");
    TEST_ASSERT_BIT_STATE_MESSAGE(CS11, cs11, TCCR1B, "Unexpected CS11");
    TEST_ASSERT_BIT_STATE_MESSAGE(CS10, cs10, TCCR1B, "Unexpected CS10");
}

int
main()
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_set_prescaller,
                   HAL_TIMER_PRESCALLER_1,
                   ~BIT(CS12),
                   ~BIT(CS11),
                   BIT(CS10));

    RUN_PARAM_TEST(should_set_prescaller,
                   HAL_TIMER_PRESCALLER_8,
                   ~BIT(CS12),
                   BIT(CS11),
                   ~BIT(CS10));

    RUN_PARAM_TEST(should_set_prescaller,
                   HAL_TIMER_PRESCALLER_64,
                   ~BIT(CS12),
                   BIT(CS11),
                   BIT(CS10));

    RUN_PARAM_TEST(should_set_prescaller,
                   HAL_TIMER_PRESCALLER_256,
                   BIT(CS12),
                   ~BIT(CS11),
                   ~BIT(CS10));

    RUN_PARAM_TEST(should_set_prescaller,
                   HAL_TIMER_PRESCALLER_1024,
                   BIT(CS12),
                   ~BIT(CS11),
                   BIT(CS10));

    return UNITY_END();
}