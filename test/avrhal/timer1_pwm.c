#include "avrhal/timer1_pwm.h"
#include "avr/io.h"
#include "helpers.h"
#include "unity_config.h"
#include <unity.h>

hal_timer1_pwm_t pwm = {
    .mode = HAL_TIMER1_PWM_FAST_8BIT,
    .channel_a =
        {
            .mode       = HAL_TIMER1_PWM_CHANNEL_DISCONNECTED,
            .duty_cycle = 0,
        },
    .channel_b =
        {
            .mode       = HAL_TIMER1_PWM_CHANNEL_DISCONNECTED,
            .duty_cycle = 0,
        },
};

void
setUp(void)
{
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1C = 0;
}

void
tearDown()
{
}

void
should_init_mode(hal_timer1_pwm_mode_t mode,
                 uint8_t               wgm13,
                 uint8_t               wgm12,
                 uint8_t               wgm11,
                 uint8_t               wgm10)
{
    // given
    pwm.mode = mode;

    // when
    hal_timer1_pwm_init(&pwm);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(WGM13, wgm13, TCCR1B, "Unexpected WGM13");
    TEST_ASSERT_BIT_STATE_MESSAGE(WGM12, wgm12, TCCR1B, "Unexpected WGM12");
    TEST_ASSERT_BIT_STATE_MESSAGE(WGM11, wgm11, TCCR1A, "Unexpected WGM11");
    TEST_ASSERT_BIT_STATE_MESSAGE(WGM10, wgm10, TCCR1A, "Unexpected WGM10");
}

void
should_init_channel_a_duty_cycle(hal_timer1_pwm_mode_t mode,
                                 uint8_t               duty_cycle,
                                 uint8_t               ocr1a)
{
    // given
    pwm.mode                 = mode;
    pwm.channel_a.duty_cycle = duty_cycle;

    // when
    hal_timer1_pwm_init(&pwm);

    // then
    TEST_ASSERT_EQUAL_HEX8(OCR1A, ocr1a);
}

void
should_init_channel_b_duty_cycle(hal_timer1_pwm_mode_t mode,
                                 uint8_t               duty_cycle,
                                 uint8_t               ocr1b)
{
    // given
    pwm.mode                 = mode;
    pwm.channel_b.duty_cycle = duty_cycle;

    // when
    hal_timer1_pwm_init(&pwm);

    // then
    TEST_ASSERT_EQUAL_HEX8(OCR1B, ocr1b);
}

void
should_run_channel_a_mode(hal_timer1_pwm_channel_mode_t mode,
                          uint8_t                       com1a1,
                          uint8_t                       com1a0)
{
    // given
    pwm.channel_a.mode = mode;

    // when
    hal_timer1_pwm_run(&pwm);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(COM1A1, com1a1, TCCR1A, "Unexpected COM1A1");
    TEST_ASSERT_BIT_STATE_MESSAGE(COM1A0, com1a0, TCCR1A, "Unexpected COM1A0");
}

void
should_run_channel_b_mode(hal_timer1_pwm_channel_mode_t mode,
                          uint8_t                       com1b1,
                          uint8_t                       com1b0)
{
    // given
    pwm.channel_b.mode = mode;

    // when
    hal_timer1_pwm_run(&pwm);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(COM1B1, com1b1, TCCR1A, "Unexpected COM1B1");
    TEST_ASSERT_BIT_STATE_MESSAGE(COM1B0, com1b0, TCCR1A, "Unexpected COM1B0");
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_init_mode,
                   HAL_TIMER1_PWM_FAST_8BIT,
                   ~BIT(WGM13),
                   BIT(WGM12),
                   ~BIT(WGM11),
                   BIT(WGM10));

    RUN_PARAM_TEST(should_init_mode,
                   HAL_TIMER1_PWM_PHASE_CORRECT_8BIT,
                   ~BIT(WGM13),
                   ~BIT(WGM12),
                   ~BIT(WGM11),
                   BIT(WGM10));

    RUN_PARAM_TEST(
        should_init_channel_a_duty_cycle, HAL_TIMER1_PWM_FAST_8BIT, 50, 0x7f);

    RUN_PARAM_TEST(
        should_init_channel_a_duty_cycle, HAL_TIMER1_PWM_FAST_8BIT, 75, 0xbf);

    RUN_PARAM_TEST(
        should_init_channel_a_duty_cycle, HAL_TIMER1_PWM_FAST_8BIT, 80, 0xcc);

    RUN_PARAM_TEST(
        should_init_channel_a_duty_cycle, HAL_TIMER1_PWM_FAST_8BIT, 100, 0xff);

    RUN_PARAM_TEST(
        should_init_channel_a_duty_cycle, HAL_TIMER1_PWM_FAST_8BIT, 101, 0xff);

    RUN_PARAM_TEST(should_init_channel_a_duty_cycle,
                   HAL_TIMER1_PWM_PHASE_CORRECT_8BIT,
                   50,
                   0x7f);

    RUN_PARAM_TEST(should_init_channel_a_duty_cycle,
                   HAL_TIMER1_PWM_PHASE_CORRECT_8BIT,
                   75,
                   0xbf);

    RUN_PARAM_TEST(should_init_channel_a_duty_cycle,
                   HAL_TIMER1_PWM_PHASE_CORRECT_8BIT,
                   80,
                   0xcc);

    RUN_PARAM_TEST(should_init_channel_a_duty_cycle,
                   HAL_TIMER1_PWM_PHASE_CORRECT_8BIT,
                   100,
                   0xff);

    RUN_PARAM_TEST(should_init_channel_a_duty_cycle,
                   HAL_TIMER1_PWM_PHASE_CORRECT_8BIT,
                   101,
                   0xff);

    RUN_PARAM_TEST(
        should_init_channel_b_duty_cycle, HAL_TIMER1_PWM_FAST_8BIT, 50, 0x7f);

    RUN_PARAM_TEST(
        should_init_channel_b_duty_cycle, HAL_TIMER1_PWM_FAST_8BIT, 75, 0xbf);

    RUN_PARAM_TEST(
        should_init_channel_b_duty_cycle, HAL_TIMER1_PWM_FAST_8BIT, 80, 0xcc);

    RUN_PARAM_TEST(
        should_init_channel_b_duty_cycle, HAL_TIMER1_PWM_FAST_8BIT, 100, 0xff);

    RUN_PARAM_TEST(
        should_init_channel_b_duty_cycle, HAL_TIMER1_PWM_FAST_8BIT, 101, 0xff);

    RUN_PARAM_TEST(should_init_channel_b_duty_cycle,
                   HAL_TIMER1_PWM_PHASE_CORRECT_8BIT,
                   50,
                   0x7f);

    RUN_PARAM_TEST(should_init_channel_b_duty_cycle,
                   HAL_TIMER1_PWM_PHASE_CORRECT_8BIT,
                   75,
                   0xbf);

    RUN_PARAM_TEST(should_init_channel_b_duty_cycle,
                   HAL_TIMER1_PWM_PHASE_CORRECT_8BIT,
                   80,
                   0xcc);

    RUN_PARAM_TEST(should_init_channel_b_duty_cycle,
                   HAL_TIMER1_PWM_PHASE_CORRECT_8BIT,
                   100,
                   0xff);

    RUN_PARAM_TEST(should_init_channel_b_duty_cycle,
                   HAL_TIMER1_PWM_PHASE_CORRECT_8BIT,
                   101,
                   0xff);

    RUN_PARAM_TEST(should_run_channel_a_mode,
                   HAL_TIMER1_PWM_CHANNEL_DISCONNECTED,
                   ~BIT(COM1A1),
                   ~BIT(COM1A0));

    RUN_PARAM_TEST(should_run_channel_a_mode,
                   HAL_TIMER1_PWM_CHANNEL_TOGGLE_ON_COMPARE,
                   ~BIT(COM1A1),
                   BIT(COM1A0));

    RUN_PARAM_TEST(should_run_channel_a_mode,
                   HAL_TIMER1_PWM_CHANNEL_NON_INVERTING,
                   BIT(COM1A1),
                   ~BIT(COM1A0));

    RUN_PARAM_TEST(should_run_channel_a_mode,
                   HAL_TIMER1_PWM_CHANNEL_INVERTING,
                   BIT(COM1A1),
                   BIT(COM1A0));

    RUN_PARAM_TEST(should_run_channel_b_mode,
                   HAL_TIMER1_PWM_CHANNEL_DISCONNECTED,
                   ~BIT(COM1B1),
                   ~BIT(COM1B0));

    RUN_PARAM_TEST(should_run_channel_b_mode,
                   HAL_TIMER1_PWM_CHANNEL_TOGGLE_ON_COMPARE,
                   ~BIT(COM1B1),
                   ~BIT(COM1B0));

    RUN_PARAM_TEST(should_run_channel_b_mode,
                   HAL_TIMER1_PWM_CHANNEL_NON_INVERTING,
                   BIT(COM1B1),
                   ~BIT(COM1B0));

    RUN_PARAM_TEST(should_run_channel_b_mode,
                   HAL_TIMER1_PWM_CHANNEL_INVERTING,
                   BIT(COM1B1),
                   BIT(COM1B0));

    return UNITY_END();
}