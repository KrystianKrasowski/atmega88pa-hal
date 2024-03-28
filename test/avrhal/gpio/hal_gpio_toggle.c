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
should_toggle(hal_gpio_register_t reg,
              uint8_t             pin,
              uint8_t             given_portx,
              uint8_t             expected_portx,
              uint8_t            *portx)
{
    // given
    *portx = given_portx;

    // when
    hal_gpio_t gpio = {reg, HAL_GPIO_OUTPUT, pin};
    hal_gpio_toggle(&gpio);

    // then
    TEST_ASSERT_EQUAL_HEX8(expected_portx, *portx);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_B, 0, 0x00, 0x01, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_B, 0, 0x01, 0x00, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_B, 1, 0x00, 0x02, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_B, 1, 0x02, 0x00, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_B, 2, 0x00, 0x04, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_B, 2, 0x04, 0x00, &PORTB);

    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_C, 0, 0x00, 0x01, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_C, 0, 0x01, 0x00, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_C, 1, 0x00, 0x02, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_C, 1, 0x02, 0x00, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_C, 2, 0x00, 0x04, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_C, 2, 0x04, 0x00, &PORTC);

    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_D, 0, 0x00, 0x01, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_D, 0, 0x01, 0x00, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_D, 1, 0x00, 0x02, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_D, 1, 0x02, 0x00, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_D, 2, 0x00, 0x04, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_REGISTER_D, 2, 0x04, 0x00, &PORTD);

    return UNITY_END();
}