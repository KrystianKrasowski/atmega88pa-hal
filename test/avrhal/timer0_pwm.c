#include "avrhal/timer0_pwm.h"
#include "avr/io.h"
#include "helpers.h"
#include "unity_config.h"
#include <unity.h>

hal_timer0_pwm_t pwm = {
    .mode = HAL_TIMER0_PWM_FAST,
    .channel_a =
        {
            .mode       = HAL_TIMER0_PWM_CHANNEL_DISCONNECTED,
            .duty_cycle = 0,
        },
    .channel_b =
        {
            .mode       = HAL_TIMER0_PWM_CHANNEL_DISCONNECTED,
            .duty_cycle = 0,
        },
};

void
setUp(void)
{
    TCCR0A = 0;
    TCCR0B = 0;
}

void
tearDown()
{
}

void
should_init_mode(hal_timer0_pwm_mode_t mode,
                 uint8_t               wgm02,
                 uint8_t               wgm01,
                 uint8_t               wgm00)
{
    // given
    pwm.mode = mode;

    // when
    hal_timer0_pwm_init(&pwm);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(WGM02, wgm02, TCCR0B, "Unexpected WGM02");
    TEST_ASSERT_BIT_STATE_MESSAGE(WGM01, wgm01, TCCR0A, "Unexpected WGM01");
    TEST_ASSERT_BIT_STATE_MESSAGE(WGM00, wgm00, TCCR0A, "Unexpected WGM00");
}

void
should_init_channel_a_duty_cycle(uint8_t duty_cycle, uint8_t ocr0a)
{
    // given
    pwm.channel_a.duty_cycle = duty_cycle;

    // when
    hal_timer0_pwm_init(&pwm);

    // then
    TEST_ASSERT_EQUAL_HEX8(OCR0A, ocr0a);
}

void
should_init_channel_b_duty_cycle(uint8_t duty_cycle, uint8_t ocr0b)
{
    // given
    pwm.channel_b.duty_cycle = duty_cycle;

    // when
    hal_timer0_pwm_init(&pwm);

    // then
    TEST_ASSERT_EQUAL_HEX8(OCR0B, ocr0b);
}

void
should_run_channel_a_mode(hal_timer0_pwm_channel_mode_t mode,
                          uint8_t                       com0a1,
                          uint8_t                       com0a0)
{
    // given
    pwm.channel_a.mode = mode;

    // when
    hal_timer0_pwm_run(&pwm);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(COM0A1, com0a1, TCCR0A, "Unexpected COM0A1");
    TEST_ASSERT_BIT_STATE_MESSAGE(COM0A0, com0a0, TCCR0A, "Unexpected COM0A0");
}

void
should_run_channel_b_mode(hal_timer0_pwm_channel_mode_t mode,
                          uint8_t                       com0b1,
                          uint8_t                       com0b0)
{
    // given
    pwm.channel_b.mode = mode;

    // when
    hal_timer0_pwm_run(&pwm);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(COM0B1, com0b1, TCCR0A, "Unexpected COM0B1");
    TEST_ASSERT_BIT_STATE_MESSAGE(COM0B0, com0b0, TCCR0A, "Unexpected COM0B0");
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_init_mode,
                   HAL_TIMER0_PWM_FAST,
                   ~BIT(WGM02),
                   BIT(WGM01),
                   BIT(WGM00));

    RUN_PARAM_TEST(should_init_mode,
                   HAL_TIMER0_PWM_PHASE_CORRECT,
                   ~BIT(WGM02),
                   ~BIT(WGM01),
                   BIT(WGM00));

    RUN_PARAM_TEST(should_init_channel_a_duty_cycle, 50, 0x7f);
    RUN_PARAM_TEST(should_init_channel_a_duty_cycle, 75, 0xbf);
    RUN_PARAM_TEST(should_init_channel_a_duty_cycle, 80, 0xcc);
    RUN_PARAM_TEST(should_init_channel_a_duty_cycle, 100, 0xff);
    RUN_PARAM_TEST(should_init_channel_a_duty_cycle, 101, 0xff);
    RUN_PARAM_TEST(should_init_channel_b_duty_cycle, 50, 0x7f);
    RUN_PARAM_TEST(should_init_channel_b_duty_cycle, 75, 0xbf);
    RUN_PARAM_TEST(should_init_channel_b_duty_cycle, 80, 0xcc);
    RUN_PARAM_TEST(should_init_channel_b_duty_cycle, 100, 0xff);
    RUN_PARAM_TEST(should_init_channel_b_duty_cycle, 101, 0xff);

    RUN_PARAM_TEST(should_run_channel_a_mode,
                   HAL_TIMER0_PWM_CHANNEL_DISCONNECTED,
                   ~BIT(COM0A1),
                   ~BIT(COM0A0));

    RUN_PARAM_TEST(should_run_channel_a_mode,
                   HAL_TIMER0_PWM_CHANNEL_TOGGLE_ON_COMPARE,
                   ~BIT(COM0A1),
                   BIT(COM0A0));

    RUN_PARAM_TEST(should_run_channel_a_mode,
                   HAL_TIMER0_PWM_CHANNEL_NON_INVERTING,
                   BIT(COM0A1),
                   ~BIT(COM0A0));

    RUN_PARAM_TEST(should_run_channel_a_mode,
                   HAL_TIMER0_PWM_CHANNEL_INVERTING,
                   BIT(COM0A1),
                   BIT(COM0A0));

    RUN_PARAM_TEST(should_run_channel_b_mode,
                   HAL_TIMER0_PWM_CHANNEL_DISCONNECTED,
                   ~BIT(COM0B1),
                   ~BIT(COM0B0));

    RUN_PARAM_TEST(should_run_channel_b_mode,
                   HAL_TIMER0_PWM_CHANNEL_TOGGLE_ON_COMPARE,
                   ~BIT(COM0B1),
                   ~BIT(COM0B0));

    RUN_PARAM_TEST(should_run_channel_b_mode,
                   HAL_TIMER0_PWM_CHANNEL_NON_INVERTING,
                   BIT(COM0B1),
                   ~BIT(COM0B0));

    RUN_PARAM_TEST(should_run_channel_b_mode,
                   HAL_TIMER0_PWM_CHANNEL_INVERTING,
                   BIT(COM0B1),
                   BIT(COM0B0));

    return UNITY_END();
}