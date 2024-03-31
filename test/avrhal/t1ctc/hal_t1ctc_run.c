#include "avr/io.h"
#include "avrhal/t1ctc.h"
#include "helpers.h"
#include "unity_config.h"
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
should_set_prescaller(hal_timer_prescaller_t prescaller,
                      uint8_t                cs12,
                      uint8_t                cs11,
                      uint8_t                cs10)
{
    // given
    timer.prescaller = prescaller;

    // when
    hal_t1ctc_run(&timer);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(CS12, cs12, TCCR1B, "Unexpected CS12");
    TEST_ASSERT_BIT_STATE_MESSAGE(CS11, cs11, TCCR1B, "Unexpected CS11");
    TEST_ASSERT_BIT_STATE_MESSAGE(CS10, cs10, TCCR1B, "Unexpected CS10");
}

int
main(void)
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