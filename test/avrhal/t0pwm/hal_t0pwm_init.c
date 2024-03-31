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
}

void
tearDown()
{
}

void
should_init_pwm_mode(hal_t0pwm_mode_t mode,
                     uint8_t          wgm02,
                     uint8_t          wgm01,
                     uint8_t          wgm00)
{
    // given
    pwm.mode = mode;

    // when
    hal_t0pwm_init(&pwm);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(WGM02, wgm02, TCCR0B, "Unexpected WGM02");
    TEST_ASSERT_BIT_STATE_MESSAGE(WGM01, wgm01, TCCR0A, "Unexpected WGM01");
    TEST_ASSERT_BIT_STATE_MESSAGE(WGM00, wgm00, TCCR0A, "Unexpected WGM00");
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_init_pwm_mode,
                   HAL_T0PWM_MODE_FAST,
                   ~BIT(WGM02),
                   BIT(WGM01),
                   BIT(WGM00));

    RUN_PARAM_TEST(should_init_pwm_mode,
                   HAL_T0PWM_MODE_PHASE_CORRECT,
                   ~BIT(WGM02),
                   ~BIT(WGM01),
                   BIT(WGM00));

    return UNITY_END();
}