#include "avr/io.h"
#include "avrhal/gpio.h"
#include "unity_config.h"
#include <unity.h>

void
setUp()
{
    DDRB = 0;
    DDRC = 0;
    DDRD = 0;
}

void
tearDown()
{
}

void
should_write_mask(hal_gpio_register_t reg,
                 uint8_t             mask,
                 uint8_t             expected_mask,
                 uint8_t            *portx)
{
    // when
    hal_gpio_write_mask(reg, mask);

    // then
    TEST_ASSERT_EQUAL_HEX8(expected_mask, *portx);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_B, 0x01, 0x01, &PORTB);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_B, 0x02, 0x02, &PORTB);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_B, 0x04, 0x04, &PORTB);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_B, 0x08, 0x08, &PORTB);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_B, 0x10, 0x10, &PORTB);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_B, 0x20, 0x20, &PORTB);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_B, 0x40, 0x40, &PORTB);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_B, 0x80, 0x80, &PORTB);

    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_C, 0x01, 0x01, &PORTC);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_C, 0x02, 0x02, &PORTC);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_C, 0x04, 0x04, &PORTC);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_C, 0x08, 0x08, &PORTC);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_C, 0x10, 0x10, &PORTC);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_C, 0x20, 0x20, &PORTC);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_C, 0x40, 0x40, &PORTC);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_C, 0x80, 0x80, &PORTC);

    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_D, 0x01, 0x01, &PORTD);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_D, 0x02, 0x02, &PORTD);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_D, 0x04, 0x04, &PORTD);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_D, 0x08, 0x08, &PORTD);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_D, 0x10, 0x10, &PORTD);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_D, 0x20, 0x20, &PORTD);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_D, 0x40, 0x40, &PORTD);
    RUN_PARAM_TEST(should_write_mask, HAL_GPIO_REGISTER_D, 0x80, 0x80, &PORTD);

    return UNITY_END();
}