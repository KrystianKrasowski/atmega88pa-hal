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
should_init_input(hal_gpio_pin_t pin, uint8_t expected_low_bit, uint8_t *ddrx)
{
    // given
    *ddrx = 0xff;

    // when
    hal_gpio_t gpio = {pin, HAL_GPIO_INPUT};
    hal_gpio_init(&gpio);

    // then
    TEST_ASSERT_BIT_LOW(expected_low_bit, *ddrx);
}

void
should_init_output(hal_gpio_pin_t pin, uint8_t expected_high_bit, uint8_t *ddrx)
{
    // given
    *ddrx = 0;

    // when
    hal_gpio_t gpio = {pin, HAL_GPIO_OUTPUT};
    hal_gpio_init(&gpio);

    // then
    TEST_ASSERT_BIT_HIGH(expected_high_bit, *ddrx);
}

void
should_init_input_pullup(hal_gpio_pin_t pin,
                         uint8_t        expected_low_ddrx,
                         uint8_t        expected_high_portx,
                         uint8_t       *ddrx,
                         uint8_t       *portx)
{
    // given
    *ddrx  = 0xff;
    *portx = 0;

    // when
    hal_gpio_t gpio = {pin, HAL_GPIO_INPUT_WITH_PULLUP};
    hal_gpio_init(&gpio);

    // then
    TEST_ASSERT_BIT_LOW(expected_low_ddrx, *ddrx);
    TEST_ASSERT_BIT_HIGH(expected_high_portx, *portx);
}

void
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PB0, DDB0, &DDRB);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PB1, DDB1, &DDRB);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PB2, DDB2, &DDRB);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PB3, DDB3, &DDRB);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PB4, DDB4, &DDRB);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PB5, DDB5, &DDRB);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PB6, DDB6, &DDRB);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PB7, DDB7, &DDRB);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PC0, DDC0, &DDRC);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PC1, DDC1, &DDRC);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PC2, DDC2, &DDRC);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PC3, DDC3, &DDRC);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PC4, DDC4, &DDRC);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PC5, DDC5, &DDRC);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PC6, DDC6, &DDRC);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PD0, DDD0, &DDRD);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PD1, DDD1, &DDRD);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PD2, DDD2, &DDRD);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PD3, DDD3, &DDRD);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PD4, DDD4, &DDRD);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PD5, DDD5, &DDRD);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PD6, DDD6, &DDRD);
    RUN_PARAM_TEST(should_init_input, HAL_GPIO_PD7, DDD7, &DDRD);

    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PB0, DDB0, &DDRB);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PB1, DDB1, &DDRB);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PB2, DDB2, &DDRB);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PB3, DDB3, &DDRB);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PB4, DDB4, &DDRB);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PB5, DDB5, &DDRB);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PB6, DDB6, &DDRB);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PB7, DDB7, &DDRB);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PC0, DDC0, &DDRC);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PC1, DDC1, &DDRC);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PC2, DDC2, &DDRC);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PC3, DDC3, &DDRC);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PC4, DDC4, &DDRC);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PC5, DDC5, &DDRC);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PC6, DDC6, &DDRC);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PD0, DDD0, &DDRD);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PD1, DDD1, &DDRD);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PD2, DDD2, &DDRD);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PD3, DDD3, &DDRD);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PD4, DDD4, &DDRD);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PD5, DDD5, &DDRD);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PD6, DDD6, &DDRD);
    RUN_PARAM_TEST(should_init_output, HAL_GPIO_PD7, DDD7, &DDRD);

    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PB0, DDB0, PORTB0, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PB1, DDB1, PORTB1, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PB2, DDB2, PORTB2, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PB3, DDB3, PORTB3, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PB4, DDB4, PORTB4, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PB5, DDB5, PORTB5, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PB6, DDB6, PORTB6, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PB7, DDB7, PORTB7, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PC0, DDC0, PORTC0, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PC1, DDC1, PORTC1, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PC2, DDC2, PORTC2, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PC3, DDC3, PORTC3, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PC4, DDC4, PORTC4, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PC5, DDC5, PORTC5, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PC6, DDC6, PORTC6, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PD0, DDD0, PORTD0, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PD1, DDD1, PORTD1, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PD2, DDD2, PORTD2, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PD3, DDD3, PORTD3, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PD4, DDD4, PORTD4, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PD5, DDD5, PORTD5, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PD6, DDD6, PORTD6, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_init_input_pullup, HAL_GPIO_PD7, DDD7, PORTD7, &DDRD, &PORTD);

    return UNITY_END();
}