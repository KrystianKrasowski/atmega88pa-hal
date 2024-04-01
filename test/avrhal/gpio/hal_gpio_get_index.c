#include "avr/io.h"
#include "avrhal/gpio.h"
#include "unity_config.h"
#include <unity.h>

hal_gpio_t gpio = {
    .pin = HAL_GPIO_PB0,
    .direction = HAL_GPIO_OUTPUT,
};

void
setUp()
{
}

void
tearDown()
{
}

void
should_get_index(hal_gpio_pin_t pin, uint8_t expected)
{
    // when
    hal_gpio_register_t actual = hal_gpio_get_index(pin);

    // then
    TEST_ASSERT_EQUAL(expected, actual);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PB0, 0);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PB1, 1);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PB2, 2);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PB3, 3);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PB4, 4);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PB5, 5);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PB6, 6);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PB7, 7);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PC0, 0);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PC1, 1);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PC2, 2);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PC3, 3);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PC4, 4);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PC5, 5);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PC6, 6);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PD0, 0);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PD1, 1);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PD2, 2);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PD3, 3);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PD4, 4);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PD5, 5);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PD6, 6);
    RUN_PARAM_TEST(should_get_index, HAL_GPIO_PD7, 7);

    return UNITY_END();
}