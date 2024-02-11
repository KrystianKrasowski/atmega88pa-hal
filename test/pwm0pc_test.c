#include "../src/pwm0pc.h"
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

void should_init_phase_correct_pwm(void)
{
  // when
  hal_pwm0pc_init();

  // then
  TEST_ASSERT_BITS(0x03, 0x01, TCCR0A);
  TEST_ASSERT_BITS(0x08, 0, TCCR0B);
}

// TODO: Parameterize it
void should_run_non_inverting_pwm_on_channel_A(void)
{
  // given
  hal_pwm0pc_def_t def = {
      .channel_a = {.mode = HAL_PWM0PC_CHANNEL_NON_INVERTING, .duty_cycle = 50},
      .channel_b = {.mode = HAL_PWM0PC_CHANNEL_DISCONNECTED, .duty_cycle = 50},
      .prescaller = HAL_PWM0PC_PRESC_1};

  // when
  hal_pwm0pc_run(&def, HAL_PWM0PC_PRESC_1);

  // then
  TEST_ASSERT_BITS(0xf0, 0x80, TCCR0A);
  TEST_ASSERT_BITS(0x0f, 0x01, TCCR0B);
}

void should_run_inverting_pwm_on_channel_A(void)
{
  // given
  hal_pwm0pc_def_t def = {
      .channel_a = {.mode = HAL_PWM0PC_CHANNEL_INVERTING, .duty_cycle = 50},
      .channel_b = {.mode = HAL_PWM0PC_CHANNEL_DISCONNECTED, .duty_cycle = 50},
      .prescaller = HAL_PWM0PC_PRESC_1};

  // when
  hal_pwm0pc_run(&def, HAL_PWM0PC_PRESC_1);

  // then
  TEST_ASSERT_BITS(0xf0, 0xc0, TCCR0A);
  TEST_ASSERT_BITS(0x0f, 0x01, TCCR0B);
}

void should_stop_pwm0pc(void)
{
  // when
  hal_pwm0pc_stop();

  // then
  TEST_ASSERT_BITS(0xf0, 0, TCCR0A);
  TEST_ASSERT_BITS(0x0f, 0, TCCR0B);
}

void setUp() {}

void tearDown() {}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(should_init_phase_correct_pwm);
  RUN_TEST(should_run_non_inverting_pwm_on_channel_A);
  RUN_TEST(should_run_inverting_pwm_on_channel_A);
  RUN_TEST(should_stop_pwm0pc);
  return UNITY_END();
}