#include "avr/io.h"
#include "avrhal/timer0_pwm.h"
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
should_set_mode(hal_timer0_pwm_mode_t mode,
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
should_set_channel_a_duty_cycle(uint8_t duty_cycle, uint8_t ocr0a)
{
    // given
    pwm.channel_a.duty_cycle = duty_cycle;

    // when
    hal_timer0_pwm_init(&pwm);

    // then
    TEST_ASSERT_EQUAL_HEX8(OCR0A, ocr0a);
}

void
should_set_channel_b_duty_cycle(uint8_t duty_cycle, uint8_t ocr0b)
{
    // given
    pwm.channel_b.duty_cycle = duty_cycle;

    // when
    hal_timer0_pwm_init(&pwm);

    // then
    TEST_ASSERT_EQUAL_HEX8(OCR0B, ocr0b);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_set_mode,
                   HAL_TIMER0_PWM_FAST,
                   ~BIT(WGM02),
                   BIT(WGM01),
                   BIT(WGM00));

    RUN_PARAM_TEST(should_set_mode,
                   HAL_TIMER0_PWM_PHASE_CORRECT,
                   ~BIT(WGM02),
                   ~BIT(WGM01),
                   BIT(WGM00));

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