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
should_get_register(hal_gpio_pin_t pin, hal_gpio_register_t expected)
{
    // given
    gpio.pin = pin;

    // when
    hal_gpio_register_t actual = hal_gpio_get_register(&gpio);

    // then
    TEST_ASSERT_EQUAL(expected, actual);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PB0, HAL_GPIO_REGISTER_B);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PB1, HAL_GPIO_REGISTER_B);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PB2, HAL_GPIO_REGISTER_B);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PB3, HAL_GPIO_REGISTER_B);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PB4, HAL_GPIO_REGISTER_B);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PB5, HAL_GPIO_REGISTER_B);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PB6, HAL_GPIO_REGISTER_B);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PB7, HAL_GPIO_REGISTER_B);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PC0, HAL_GPIO_REGISTER_C);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PC1, HAL_GPIO_REGISTER_C);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PC2, HAL_GPIO_REGISTER_C);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PC3, HAL_GPIO_REGISTER_C);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PC4, HAL_GPIO_REGISTER_C);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PC5, HAL_GPIO_REGISTER_C);
    RUN_PARAM_TEST(should_get_register, HAL_GPIO_PC6, HAL_GPIO_REGISTER_C);

    return UNITY_END();
}