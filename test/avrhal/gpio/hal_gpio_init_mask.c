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
should_init_mask(hal_gpio_register_t reg,
                 uint8_t             mask,
                 uint8_t             expected_mask,
                 uint8_t            *ddrx)
{
    // when
    hal_gpio_init_mask(reg, mask);

    // then
    TEST_ASSERT_EQUAL_HEX8(expected_mask, *ddrx);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_B, 0x01, 0x01, &DDRB);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_B, 0x02, 0x02, &DDRB);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_B, 0x04, 0x04, &DDRB);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_B, 0x08, 0x08, &DDRB);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_B, 0x10, 0x10, &DDRB);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_B, 0x20, 0x20, &DDRB);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_B, 0x40, 0x40, &DDRB);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_B, 0x80, 0x80, &DDRB);

    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_C, 0x01, 0x01, &DDRC);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_C, 0x02, 0x02, &DDRC);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_C, 0x04, 0x04, &DDRC);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_C, 0x08, 0x08, &DDRC);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_C, 0x10, 0x10, &DDRC);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_C, 0x20, 0x20, &DDRC);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_C, 0x40, 0x40, &DDRC);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_C, 0x80, 0x80, &DDRC);

    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_D, 0x01, 0x01, &DDRD);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_D, 0x02, 0x02, &DDRD);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_D, 0x04, 0x04, &DDRD);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_D, 0x08, 0x08, &DDRD);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_D, 0x10, 0x10, &DDRD);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_D, 0x20, 0x20, &DDRD);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_D, 0x40, 0x40, &DDRD);
    RUN_PARAM_TEST(should_init_mask, HAL_GPIO_REGISTER_D, 0x80, 0x80, &DDRD);

    return UNITY_END();
}