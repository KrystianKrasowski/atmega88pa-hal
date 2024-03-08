#include "t1int.h"
#include "unity_config.h"
#include <unity/unity.h>

static uint8_t global_interrupt_enable = 0;

uint8_t  TIMSK1 = 0;
uint16_t ICR1   = 0;
void
sei(void)
{
    global_interrupt_enable = 1;
}

void
should_configure_interrupts(uint8_t toie,
                            uint8_t ocie1a,
                            uint8_t ocie1b,
                            uint8_t icie1,
                            uint8_t expected)
{
    // when
    hal_t1int_cfg_t cfg = {
        .timer_overflow   = toie,
        .output_compare_a = ocie1a,
        .output_compare_b = ocie1b,
        .input_capture    = icie1,
    };
    hal_t1int_configure(&cfg);

    // then
    TEST_ASSERT_BITS(0xff, expected, TIMSK1);
    TEST_ASSERT_EQUAL(1, global_interrupt_enable);
}

void
setUp()
{
}

void
tearDown()
{
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_configure_interrupts, 1, 0, 0, 0, 0x01);
    RUN_TEST(should_configure_interrupts, 0, 1, 0, 0, 0x02);
    RUN_TEST(should_configure_interrupts, 0, 0, 1, 0, 0x04);
    RUN_TEST(should_configure_interrupts, 0, 0, 1, 0, 0x04);
    RUN_TEST(should_configure_interrupts, 1, 1, 0, 0, 0x03);
    RUN_TEST(should_configure_interrupts, 1, 0, 1, 0, 0x05);
    RUN_TEST(should_configure_interrupts, 1, 0, 0, 1, 0x21);
    RUN_TEST(should_configure_interrupts, 1, 1, 1, 0, 0x07);
    RUN_TEST(should_configure_interrupts, 1, 1, 0, 1, 0x23);
    RUN_TEST(should_configure_interrupts, 1, 1, 1, 1, 0x27);
    RUN_TEST(should_configure_interrupts, 0, 1, 1, 1, 0x26);
    RUN_TEST(should_configure_interrupts, 1, 0, 1, 1, 0x25);
    RUN_TEST(should_configure_interrupts, 1, 1, 0, 1, 0x23);
    RUN_TEST(should_configure_interrupts, 1, 0, 0, 1, 0x21);
    RUN_TEST(should_configure_interrupts, 0, 1, 1, 0, 0x06);
    RUN_TEST(should_configure_interrupts, 0, 0, 1, 1, 0x24);
    return UNITY_END();
}
