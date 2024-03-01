#include "t1ctc.h"
#include "unity_config.h"
#include <unity/unity.h>

#define BIT(index) (1 << index)

uint8_t TCCR1A = 0;
uint8_t WGM10 = 0;
uint8_t WGM11 = 1;

uint8_t TCCR1B = 0;
uint8_t WGM12 = 3;
uint8_t CS10 = 0;
uint8_t CS11 = 1;
uint8_t CS12 = 2;

uint16_t OCR1A = 0;

hal_t1ctc_def_t t1ctc = {.prescaller = HAL_TIMER_PRESCALLER_1};

void setUp()
{
  TCCR1A = 0;
  TCCR1B = 0;
}

void tearDown() {}

void should_init_timer1_ctc_mode(void)
{ 
  // when
  hal_t1ctc_init(&t1ctc);

  // then
  TEST_ASSERT_BITS(0xff, 0, TCCR1A);
  TEST_ASSERT_BITS(0xff, BIT(WGM12), TCCR1B);
}

void should_init_timer1_ctc_mode_resolution(uint16_t resolution)
{
  // given
  t1ctc.resolution = resolution;

  // when
  hal_t1ctc_init(&t1ctc);

  // then
  TEST_ASSERT_BITS(0xff, resolution, OCR1A);
}

void should_run_timer1_ctc_mode(hal_timer_prescaller_t prescaller, uint8_t tccr1b)
{
  // given
  t1ctc.prescaller = prescaller;

  // when
  hal_t1ctc_run(&t1ctc);

  // then
  TEST_ASSERT_BITS(0xff, tccr1b, TCCR1B);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(should_init_timer1_ctc_mode);
  RUN_TEST(should_init_timer1_ctc_mode_resolution, 0x01);
  RUN_TEST(should_init_timer1_ctc_mode_resolution, 0x02);
  RUN_TEST(should_init_timer1_ctc_mode_resolution, 0x03);
  RUN_TEST(should_init_timer1_ctc_mode_resolution, 0x04);
  RUN_TEST(should_init_timer1_ctc_mode_resolution, 0x05);
  RUN_TEST(should_run_timer1_ctc_mode, HAL_TIMER_PRESCALLER_1, BIT(CS10));
  RUN_TEST(should_run_timer1_ctc_mode, HAL_TIMER_PRESCALLER_8, BIT(CS11));
  RUN_TEST(should_run_timer1_ctc_mode, HAL_TIMER_PRESCALLER_64, BIT(CS11) | BIT(CS10));
  RUN_TEST(should_run_timer1_ctc_mode, HAL_TIMER_PRESCALLER_256, BIT(CS12));
  RUN_TEST(should_run_timer1_ctc_mode, HAL_TIMER_PRESCALLER_1024, BIT(CS12) | BIT(CS10));
  return UNITY_END();
}
