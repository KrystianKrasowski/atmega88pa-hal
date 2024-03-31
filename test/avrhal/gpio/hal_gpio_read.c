#include "avr/io.h"
#include "avrhal/gpio.h"
#include "unity_config.h"
#include <unity.h>

void
setUp()
{
}

void
tearDown()
{
}

void
should_read(hal_gpio_pin_t   pin,
            uint8_t          given_pinx,
            hal_gpio_state_t expected_state,
            uint8_t         *pinx)
{
    // given
    *pinx = given_pinx;

    // when
    hal_gpio_t gpio = {pin, HAL_GPIO_INPUT};
    hal_gpio_state_t state = hal_gpio_read(&gpio);

    // then
    TEST_ASSERT_EQUAL(expected_state, state);
}

void
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_read, HAL_GPIO_PB0, 0x01, HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB0, 0x00, HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB1, 0x02, HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB1, 0x00, HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB2, 0x04, HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB2, 0x00, HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB3, 0x08, HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB3, 0x00, HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB4, 0x10, HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB4, 0x00, HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB5, 0x20, HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB5, 0x00, HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB6, 0x40, HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB6, 0x00, HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB7, 0x80, HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PB7, 0x00, HAL_GPIO_LOW, &PINB);

    RUN_PARAM_TEST(should_read, HAL_GPIO_PC0, 0x01, HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC0, 0x00, HAL_GPIO_LOW, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC1, 0x02, HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC1, 0x00, HAL_GPIO_LOW, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC2, 0x04, HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC2, 0x00, HAL_GPIO_LOW, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC3, 0x08, HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC3, 0x00, HAL_GPIO_LOW, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC4, 0x10, HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC4, 0x00, HAL_GPIO_LOW, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC5, 0x20, HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC5, 0x00, HAL_GPIO_LOW, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC6, 0x40, HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PC6, 0x00, HAL_GPIO_LOW, &PINC);

    RUN_PARAM_TEST(should_read, HAL_GPIO_PD0, 0x01, HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD0, 0x00, HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD1, 0x02, HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD1, 0x00, HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD2, 0x04, HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD2, 0x00, HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD3, 0x08, HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD3, 0x00, HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD4, 0x10, HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD4, 0x00, HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD5, 0x20, HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD5, 0x00, HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD6, 0x40, HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD6, 0x00, HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD7, 0x80, HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(should_read, HAL_GPIO_PD7, 0x00, HAL_GPIO_LOW, &PIND);

    return UNITY_END();
}