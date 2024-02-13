#include "t0pwm.h"
#include "unity_config.h"
#include <unity/unity.h>

uint8_t TCCR0A = 0;
uint8_t TCCR0B = 0;
uint8_t TCNT0 = 0;
uint8_t OCR0A = 0;
uint8_t OCR0B = 0;
uint8_t WGM00 = 0;
uint8_t WGM01 = 1;
uint8_t WGM02 = 3;
uint8_t COM0A1 = 7;
uint8_t COM0A0 = 6;
uint8_t COM0B1 = 5;
uint8_t COM0B0 = 4;
uint8_t CS02 = 2;
uint8_t CS01 = 1;
uint8_t CS00 = 0;

hal_t0pwm_def_t pwm = {
      .mode = HAL_T0PWM_MODE_FAST,
      .channel_a = {.mode = HAL_T0PWM_CHANNEL_NON_INVERTING, .duty_cycle = 50},
      .channel_b = {.mode = HAL_T0PWM_CHANNEL_DISCONNECTED, .duty_cycle = 0},
      .prescaller = HAL_T0PWM_PRESC_1};

void should_init_fast_pwm(void)
{
  // when
  pwm.mode = HAL_T0PWM_MODE_FAST;
  hal_t0pwm_init(&pwm);

  // then
  TEST_ASSERT_BITS(0x0f, 0x03, TCCR0A);
}

void should_init_phase_correct_pwm(void)
{
  // when
  pwm.mode = HAL_T0PWM_MODE_PHASE_CORRECT;
  hal_t0pwm_init(&pwm);

  // then
  TEST_ASSERT_BITS(0x03, 0x01, TCCR0A);
  TEST_ASSERT_BITS(0x08, 0, TCCR0B);
}

void should_run_pwm_with_channel_mode(hal_t0pwm_channel_mode_t channel_a_mode,
                              hal_t0pwm_channel_mode_t channel_b_mode,
                              uint8_t expected_tccr0a)
{
  // when
  pwm.channel_a.mode = channel_a_mode;
  pwm.channel_b.mode = channel_b_mode;
  hal_t0pwm_run(&pwm);

  // then
  TEST_ASSERT_BITS(0xf0, expected_tccr0a, TCCR0A);
}

void should_run_pwm_with_duty_cycle(uint8_t channel_a_dc,
                                    uint8_t channel_b_dc,
                                    uint8_t ocr0a,
                                    uint8_t ocr0b)
{
  // when
  pwm.channel_a.duty_cycle = channel_a_dc;
  pwm.channel_b.duty_cycle = channel_b_dc;
  hal_t0pwm_run(&pwm);

  // then
  TEST_ASSERT_EQUAL_HEX(ocr0a, OCR0A);
  TEST_ASSERT_EQUAL_HEX(ocr0b, OCR0B);
}

void should_run_pwm_with_prescaler(hal_t0pwm_prescaller_t presc, uint8_t tccr0b)
{
  // when
  pwm.prescaller = presc;
  hal_t0pwm_run(&pwm);

  // then
  TEST_ASSERT_BITS(0x0f, tccr0b, TCCR0B);
}

void should_stop_pwm(void)
{
  // when
  hal_t0pwm_stop();

  // then
  TEST_ASSERT_BITS(0xf0, 0, TCCR0A);
  TEST_ASSERT_BITS(0x0f, 0, TCCR0B);
}

void setUp() {}

void tearDown() {}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(should_init_fast_pwm);
  RUN_TEST(should_init_phase_correct_pwm);
  RUN_TEST(should_run_pwm_with_channel_mode,
           HAL_T0PWM_CHANNEL_DISCONNECTED,
           HAL_T0PWM_CHANNEL_DISCONNECTED,
           0x00);
  RUN_TEST(should_run_pwm_with_channel_mode,
           HAL_T0PWM_CHANNEL_TOGGLE_ON_COMPARE,
           HAL_T0PWM_CHANNEL_DISCONNECTED,
           0x40);
  RUN_TEST(should_run_pwm_with_channel_mode,
           HAL_T0PWM_CHANNEL_NON_INVERTING,
           HAL_T0PWM_CHANNEL_DISCONNECTED,
           0x80);
  RUN_TEST(should_run_pwm_with_channel_mode,
           HAL_T0PWM_CHANNEL_INVERTING,
           HAL_T0PWM_CHANNEL_DISCONNECTED,
           0xc0);
  // According to atmega88pa datasheet, channel B has no compare match mode,
  // thus this HAL use case falls back to disconnected mode on channel B
  RUN_TEST(should_run_pwm_with_channel_mode,
           HAL_T0PWM_CHANNEL_DISCONNECTED,
           HAL_T0PWM_CHANNEL_TOGGLE_ON_COMPARE,
           0x00);
  RUN_TEST(should_run_pwm_with_channel_mode,
           HAL_T0PWM_CHANNEL_DISCONNECTED,
           HAL_T0PWM_CHANNEL_NON_INVERTING,
           0x20);
  RUN_TEST(should_run_pwm_with_channel_mode,
           HAL_T0PWM_CHANNEL_DISCONNECTED,
           HAL_T0PWM_CHANNEL_INVERTING,
           0x30);
  RUN_TEST(should_run_pwm_with_duty_cycle, 50, 50, 0x7f, 0x7f);
  RUN_TEST(should_run_pwm_with_duty_cycle, 75, 75, 0xbf, 0xbf);
  RUN_TEST(should_run_pwm_with_duty_cycle, 80, 75, 0xcc, 0xbf);
  RUN_TEST(should_run_pwm_with_duty_cycle, 100, 100, 0xff, 0xff);
  RUN_TEST(should_run_pwm_with_duty_cycle, 101, 101, 0xff, 0xff);
  // cannot pass less than 0 as duty cycle var is of unsigned char type
  RUN_TEST(should_run_pwm_with_duty_cycle, -5, -5, 0xff, 0xff);
  RUN_TEST(should_run_pwm_with_prescaler, HAL_T0PWM_PRESC_1, 0x01);
  RUN_TEST(should_run_pwm_with_prescaler, HAL_T0PWM_PRESC_8, 0x02);
  RUN_TEST(should_run_pwm_with_prescaler, HAL_T0PWM_PRESC_64, 0x03);
  RUN_TEST(should_run_pwm_with_prescaler, HAL_T0PWM_PRESC_256, 0x04);
  RUN_TEST(should_run_pwm_with_prescaler, HAL_T0PWM_PRESC_1024, 0x05);
  RUN_TEST(should_run_pwm_with_prescaler, -1, 0x00);
  RUN_TEST(should_stop_pwm);
  return UNITY_END();
}