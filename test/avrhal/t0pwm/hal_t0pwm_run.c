#include "avr/io.h"
#include "avrhal/t0pwm.h"
#include "helpers.h"
#include "unity_config.h"
#include <unity.h>

hal_t0pwm_t pwm = {
    .mode = HAL_T0PWM_MODE_FAST,
    .channel_a =
        {
            .mode       = HAL_T0PWM_CHANNEL_DISCONNECTED,
            .duty_cycle = 0,
        },
    .channel_b =
        {
            .mode       = HAL_T0PWM_CHANNEL_DISCONNECTED,
            .duty_cycle = 0,
        },
    .prescaller = HAL_TIMER_PRESCALLER_1,
};

void
setUp(void)
{
    TCCR0A = 0;
    TCCR0B = 0;
    OCR0A  = 0;
    OCR0B  = 0;
}

void
tearDown()
{
}

void
should_set_channel_a_mode(hal_t0pwm_channel_mode_t mode,
                          uint8_t                  com0a1,
                          uint8_t                  com0a0)
{
    // given
    pwm.channel_a.mode = mode;

    // when
    hal_t0pwm_run(&pwm);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(COM0A1, com0a1, TCCR0A, "Unexpectec COM0A1");
    TEST_ASSERT_BIT_STATE_MESSAGE(COM0A0, com0a0, TCCR0A, "Unexpectec COM0A0");
}

void
should_set_channel_b_mode(hal_t0pwm_channel_mode_t mode,
                          uint8_t                  com0b1,
                          uint8_t                  com0b0)
{
    // given
    pwm.channel_b.mode = mode;

    // when
    hal_t0pwm_run(&pwm);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(COM0B1, com0b1, TCCR0A, "Unexpectec COM0B1");
    TEST_ASSERT_BIT_STATE_MESSAGE(COM0B0, com0b0, TCCR0A, "Unexpectec COM0B0");
}

void
should_set_prescaller(hal_timer_prescaller_t prescaller,
                      uint8_t                cs02,
                      uint8_t                cs01,
                      uint8_t                cs00)
{
    // given
    pwm.prescaller = prescaller;

    // when
    hal_t0pwm_run(&pwm);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(CS02, cs02, TCCR0B, "Unexpected CS02");
    TEST_ASSERT_BIT_STATE_MESSAGE(CS01, cs01, TCCR0B, "Unexpected CS01");
    TEST_ASSERT_BIT_STATE_MESSAGE(CS00, cs00, TCCR0B, "Unexpected CS00");
}

void
should_set_channel_a_duty_cycle(uint8_t duty_cycle, uint8_t ocr0a)
{
    // given
    pwm.channel_a.duty_cycle = duty_cycle;

    // when
    hal_t0pwm_run(&pwm);

    // then
    TEST_ASSERT_EQUAL_HEX8(OCR0A, ocr0a);
}

void
should_set_channel_b_duty_cycle(uint8_t duty_cycle, uint8_t ocr0b)
{
    // given
    pwm.channel_b.duty_cycle = duty_cycle;

    // when
    hal_t0pwm_run(&pwm);

    // then
    TEST_ASSERT_EQUAL_HEX8(OCR0B, ocr0b);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_set_channel_a_mode,
                   HAL_T0PWM_CHANNEL_DISCONNECTED,
                   ~BIT(COM0A1),
                   ~BIT(COM0A0));

    RUN_PARAM_TEST(should_set_channel_a_mode,
                   HAL_T0PWM_CHANNEL_TOGGLE_ON_COMPARE,
                   ~BIT(COM0A1),
                   BIT(COM0A0));

    RUN_PARAM_TEST(should_set_channel_a_mode,
                   HAL_T0PWM_CHANNEL_NON_INVERTING,
                   BIT(COM0A1),
                   ~BIT(COM0A0));

    RUN_PARAM_TEST(should_set_channel_a_mode,
                   HAL_T0PWM_CHANNEL_INVERTING,
                   BIT(COM0A1),
                   BIT(COM0A0));

    RUN_PARAM_TEST(should_set_channel_b_mode,
                   HAL_T0PWM_CHANNEL_DISCONNECTED,
                   ~BIT(COM0B1),
                   ~BIT(COM0B0));

    RUN_PARAM_TEST(should_set_channel_b_mode,
                   HAL_T0PWM_CHANNEL_TOGGLE_ON_COMPARE,
                   ~BIT(COM0B1),
                   ~BIT(COM0B0));

    RUN_PARAM_TEST(should_set_channel_b_mode,
                   HAL_T0PWM_CHANNEL_NON_INVERTING,
                   BIT(COM0B1),
                   ~BIT(COM0B0));

    RUN_PARAM_TEST(should_set_channel_b_mode,
                   HAL_T0PWM_CHANNEL_INVERTING,
                   BIT(COM0B1),
                   BIT(COM0B0));

    RUN_PARAM_TEST(should_set_prescaller,
                   HAL_TIMER_PRESCALLER_1,
                   ~BIT(CS02),
                   ~BIT(CS01),
                   BIT(CS00));

    RUN_PARAM_TEST(should_set_prescaller,
                   HAL_TIMER_PRESCALLER_8,
                   ~BIT(CS02),
                   BIT(CS01),
                   ~BIT(CS00));

    RUN_PARAM_TEST(should_set_prescaller,
                   HAL_TIMER_PRESCALLER_64,
                   ~BIT(CS02),
                   BIT(CS01),
                   BIT(CS00));

    RUN_PARAM_TEST(should_set_prescaller,
                   HAL_TIMER_PRESCALLER_256,
                   BIT(CS02),
                   ~BIT(CS01),
                   ~BIT(CS00));

    RUN_PARAM_TEST(should_set_prescaller,
                   HAL_TIMER_PRESCALLER_1024,
                   BIT(CS02),
                   ~BIT(CS01),
                   BIT(CS00));

    RUN_PARAM_TEST(should_set_prescaller,
                   HAL_TIMER_PRESCALLER_NONE,
                   ~BIT(CS02),
                   ~BIT(CS01),
                   ~BIT(CS00));

    RUN_PARAM_TEST(should_set_channel_a_duty_cycle, 50, 0x7f);
    RUN_PARAM_TEST(should_set_channel_a_duty_cycle, 75, 0xbf);
    RUN_PARAM_TEST(should_set_channel_a_duty_cycle, 80, 0xcc);
    RUN_PARAM_TEST(should_set_channel_a_duty_cycle, 100, 0xff);
    RUN_PARAM_TEST(should_set_channel_a_duty_cycle, 101, 0xff);
    RUN_PARAM_TEST(should_set_channel_b_duty_cycle, 50, 0x7f);
    RUN_PARAM_TEST(should_set_channel_b_duty_cycle, 75, 0xbf);
    RUN_PARAM_TEST(should_set_channel_b_duty_cycle, 80, 0xcc);
    RUN_PARAM_TEST(should_set_channel_b_duty_cycle, 100, 0xff);
    RUN_PARAM_TEST(should_set_channel_b_duty_cycle, 101, 0xff);

    return UNITY_END();
}