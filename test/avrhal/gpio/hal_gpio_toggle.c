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
should_toggle(hal_gpio_pin_t pin,
              uint8_t        given_portx,
              uint8_t        expected_portx,
              uint8_t       *portx)
{
    // given
    *portx = given_portx;

    // when
    hal_gpio_t gpio = {pin, HAL_GPIO_OUTPUT};
    hal_gpio_toggle(&gpio);

    // then
    TEST_ASSERT_EQUAL_HEX8(expected_portx, *portx);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB0, 0x00, 0x01, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB0, 0x01, 0x00, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB1, 0x00, 0x02, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB1, 0x02, 0x00, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB2, 0x00, 0x04, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB2, 0x04, 0x00, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB3, 0x00, 0x08, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB3, 0x08, 0x00, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB4, 0x00, 0x10, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB4, 0x10, 0x00, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB5, 0x00, 0x20, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB5, 0x20, 0x00, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB6, 0x00, 0x40, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB6, 0x40, 0x00, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB7, 0x00, 0x80, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PB7, 0x80, 0x00, &PORTB);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC0, 0x00, 0x01, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC0, 0x01, 0x00, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC1, 0x00, 0x02, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC1, 0x02, 0x00, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC2, 0x00, 0x04, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC2, 0x04, 0x00, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC3, 0x00, 0x08, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC3, 0x08, 0x00, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC4, 0x00, 0x10, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC4, 0x10, 0x00, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC5, 0x00, 0x20, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC5, 0x20, 0x00, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC6, 0x00, 0x40, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PC6, 0x40, 0x00, &PORTC);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD0, 0x00, 0x01, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD0, 0x01, 0x00, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD1, 0x00, 0x02, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD1, 0x02, 0x00, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD2, 0x00, 0x04, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD2, 0x04, 0x00, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD3, 0x00, 0x08, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD3, 0x08, 0x00, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD4, 0x00, 0x10, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD4, 0x10, 0x00, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD5, 0x00, 0x20, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD5, 0x20, 0x00, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD6, 0x00, 0x40, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD6, 0x40, 0x00, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD7, 0x00, 0x80, &PORTD);
    RUN_PARAM_TEST(should_toggle, HAL_GPIO_PD7, 0x80, 0x00, &PORTD);

    return UNITY_END();
}