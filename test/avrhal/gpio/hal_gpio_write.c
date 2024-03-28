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
should_write(hal_gpio_register_t reg,
             uint8_t             pin,
             hal_gpio_state_t    state,
             uint8_t             given_portx,
             uint8_t             expected_portx,
             uint8_t            *portx)
{
    // given
    *portx = given_portx;

    // when
    hal_gpio_t gpio = {reg, HAL_GPIO_OUTPUT, pin};
    hal_gpio_write(&gpio, state);

    // then
    TEST_ASSERT_EQUAL_HEX8(expected_portx, *portx);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_write,
                   HAL_GPIO_REGISTER_B,
                   0,
                   HAL_GPIO_HIGH,
                   0x00,
                   0x01,
                   &PORTB);
    
    RUN_PARAM_TEST(should_write,
                   HAL_GPIO_REGISTER_B,
                   0,
                   HAL_GPIO_LOW,
                   0x01,
                   0x00,
                   &PORTB);

    RUN_PARAM_TEST(should_write,
                   HAL_GPIO_REGISTER_C,
                   2,
                   HAL_GPIO_HIGH,
                   0x00,
                   0x04,
                   &PORTC);
    
    RUN_PARAM_TEST(should_write,
                   HAL_GPIO_REGISTER_C,
                   2,
                   HAL_GPIO_LOW,
                   0x04,
                   0x00,
                   &PORTC);

    RUN_PARAM_TEST(should_write,
                   HAL_GPIO_REGISTER_D,
                   3,
                   HAL_GPIO_HIGH,
                   0x00,
                   0x08,
                   &PORTD);
    
    RUN_PARAM_TEST(should_write,
                   HAL_GPIO_REGISTER_D,
                   3,
                   HAL_GPIO_LOW,
                   0x08,
                   0x00,
                   &PORTD);

    return UNITY_END();
}