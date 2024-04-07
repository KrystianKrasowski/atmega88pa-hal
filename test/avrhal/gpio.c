#include "avr/io.h"
#include "avrhal/gpio.h"
#include "helpers.h"
#include "unity_config.h"
#include <unity.h>

void
setUp(void)
{
    DDRB  = 0;
    DDRC  = 0;
    DDRD  = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
}

void
tearDown(void)
{
}

void
should_define_output(hal_gpio_pin_t pin, uint8_t ddxn, uint8_t *ddrx)
{
    // when
    hal_gpio_t gpio = {pin, HAL_GPIO_OUTPUT};
    hal_gpio_define(&gpio);
    hal_gpio_update();

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(ddxn, BIT(ddxn), *ddrx, "Unexpected DDxn");
}

void
should_define_input(hal_gpio_pin_t pin, uint8_t ddxn, uint8_t *ddrx)
{
    // given
    DDRB = 0xff;
    DDRC = 0xff;
    DDRD = 0xff;

    // when
    hal_gpio_t gpio = {pin, HAL_GPIO_INPUT};
    hal_gpio_define(&gpio);
    hal_gpio_update();

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(ddxn, ~BIT(ddxn), *ddrx, "Unexpected DDxn");
}

void
should_define_input_pullup(hal_gpio_pin_t pin,
                           uint8_t         ddxn,
                           uint8_t         portxn,
                           uint8_t        *ddrx,
                           uint8_t        *portx)
{
    // given
    DDRB = 0xff;
    DDRC = 0xff;
    DDRD = 0xff;

    // when
    hal_gpio_t gpio = {pin, HAL_GPIO_INPUT_WITH_PULLUP};
    hal_gpio_define(&gpio);
    hal_gpio_update();

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(ddxn, ~BIT(ddxn), *ddrx, "Unexpected DDxn");
    TEST_ASSERT_BIT_STATE_MESSAGE(
        portxn, BIT(portxn), *portx, "Unexpected PORTxn");
}

void
should_define_many_gpio(void)
{
    // given
    hal_gpio_t gpioB0 = {HAL_GPIO_PB0, HAL_GPIO_OUTPUT};
    hal_gpio_t gpioB1 = {HAL_GPIO_PB1, HAL_GPIO_INPUT};
    hal_gpio_t gpioB2 = {HAL_GPIO_PB2, HAL_GPIO_OUTPUT};
    hal_gpio_t gpioB3 = {HAL_GPIO_PB3, HAL_GPIO_INPUT};
    hal_gpio_t gpioB4 = {HAL_GPIO_PB4, HAL_GPIO_OUTPUT};
    hal_gpio_t gpioB5 = {HAL_GPIO_PB5, HAL_GPIO_INPUT_WITH_PULLUP};
    hal_gpio_t gpioB6 = {HAL_GPIO_PB6, HAL_GPIO_OUTPUT};
    hal_gpio_t gpioB7 = {HAL_GPIO_PB7, HAL_GPIO_INPUT_WITH_PULLUP};

    hal_gpio_t gpioC0 = {HAL_GPIO_PC0, HAL_GPIO_OUTPUT};
    hal_gpio_t gpioC1 = {HAL_GPIO_PC1, HAL_GPIO_OUTPUT};
    hal_gpio_t gpioC2 = {HAL_GPIO_PC2, HAL_GPIO_OUTPUT};
    hal_gpio_t gpioC3 = {HAL_GPIO_PC3, HAL_GPIO_OUTPUT};
    hal_gpio_t gpioC4 = {HAL_GPIO_PC4, HAL_GPIO_INPUT_WITH_PULLUP};
    hal_gpio_t gpioC5 = {HAL_GPIO_PC5, HAL_GPIO_INPUT_WITH_PULLUP};
    hal_gpio_t gpioC6 = {HAL_GPIO_PC6, HAL_GPIO_INPUT};

    hal_gpio_t gpioD0 = {HAL_GPIO_PD0, HAL_GPIO_INPUT_WITH_PULLUP};
    hal_gpio_t gpioD1 = {HAL_GPIO_PD1, HAL_GPIO_OUTPUT};
    hal_gpio_t gpioD2 = {HAL_GPIO_PD2, HAL_GPIO_INPUT_WITH_PULLUP};
    hal_gpio_t gpioD3 = {HAL_GPIO_PD3, HAL_GPIO_OUTPUT};
    hal_gpio_t gpioD4 = {HAL_GPIO_PD4, HAL_GPIO_INPUT};
    hal_gpio_t gpioD5 = {HAL_GPIO_PD5, HAL_GPIO_OUTPUT};
    hal_gpio_t gpioD6 = {HAL_GPIO_PD6, HAL_GPIO_INPUT};
    hal_gpio_t gpioD7 = {HAL_GPIO_PD7, HAL_GPIO_OUTPUT};

    // when
    hal_gpio_define(&gpioB0);
    hal_gpio_define(&gpioB1);
    hal_gpio_define(&gpioB2);
    hal_gpio_define(&gpioB3);
    hal_gpio_define(&gpioB4);
    hal_gpio_define(&gpioB5);
    hal_gpio_define(&gpioB6);
    hal_gpio_define(&gpioB7);

    hal_gpio_define(&gpioC0);
    hal_gpio_define(&gpioC1);
    hal_gpio_define(&gpioC2);
    hal_gpio_define(&gpioC3);
    hal_gpio_define(&gpioC4);
    hal_gpio_define(&gpioC5);
    hal_gpio_define(&gpioC6);

    hal_gpio_define(&gpioD0);
    hal_gpio_define(&gpioD1);
    hal_gpio_define(&gpioD2);
    hal_gpio_define(&gpioD3);
    hal_gpio_define(&gpioD4);
    hal_gpio_define(&gpioD5);
    hal_gpio_define(&gpioD6);
    hal_gpio_define(&gpioD7);
    hal_gpio_update();

    // then
    TEST_ASSERT_EQUAL_HEX8(0b01010101, DDRB);
    TEST_ASSERT_EQUAL_HEX8(0b10100000, PORTB);
    TEST_ASSERT_EQUAL_HEX8(0b00001111, DDRC);
    TEST_ASSERT_EQUAL_HEX8(0b00110000, PORTC);
    TEST_ASSERT_EQUAL_HEX8(0b10101010, DDRD);
    TEST_ASSERT_EQUAL_HEX8(0b00000101, PORTD);
}

void
should_set_gpio(hal_gpio_pin_t pin, uint8_t portxn, uint8_t *portx)
{
    // given
    hal_gpio_t gpio = {pin, HAL_GPIO_OUTPUT};
    hal_gpio_define(&gpio);
    hal_gpio_update();

    // when
    hal_gpio_set(&gpio, HAL_GPIO_HIGH);
    hal_gpio_update();

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(
        portxn, BIT(portxn), *portx, "Unexpected PORTxn");
}

void
should_unset_gpio(hal_gpio_pin_t pin, uint8_t portxn, uint8_t *portx)
{
    // given
    *portx = 0;
    hal_gpio_t gpio = {pin, HAL_GPIO_OUTPUT};
    hal_gpio_define(&gpio);
    hal_gpio_update();

    // when
    hal_gpio_set(&gpio, HAL_GPIO_LOW);
    hal_gpio_update();

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(
        portxn, ~BIT(portxn), *portx, "Unexpected PORTxn");
}

void
should_toggle_gpio(hal_gpio_pin_t pin, uint8_t bit_index, uint8_t *portx)
{
    // given
    *portx = 0;
    hal_gpio_t gpio = {pin, HAL_GPIO_OUTPUT};
    hal_gpio_define(&gpio);
    hal_gpio_update();

    // when
    hal_gpio_toggle(&gpio);
    hal_gpio_update();

    // then
    TEST_ASSERT_BIT_HIGH(bit_index, *portx);

    // when
    hal_gpio_toggle(&gpio);
    hal_gpio_update();

    // then
    TEST_ASSERT_BIT_LOW(bit_index, *portx);
}

void
should_read_gpio(hal_gpio_pin_t   pin,
                 uint8_t           pinx_value,
                 hal_gpio_state_t expected,
                 uint8_t          *pinx)
{
    // given
    hal_gpio_t gpio = {pin, HAL_GPIO_OUTPUT};
    hal_gpio_define(&gpio);
    hal_gpio_update();
    *pinx = pinx_value;

    // when
    hal_gpio_state_t state = hal_gpio_read(&gpio);

    // then
    TEST_ASSERT_EQUAL(expected, state);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PB0, DDB0, &DDRB);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PB1, DDB1, &DDRB);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PB2, DDB2, &DDRB);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PB3, DDB3, &DDRB);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PB4, DDB4, &DDRB);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PB5, DDB5, &DDRB);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PB6, DDB6, &DDRB);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PB7, DDB7, &DDRB);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PC0, DDC0, &DDRC);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PC1, DDC1, &DDRC);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PC2, DDC2, &DDRC);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PC3, DDC3, &DDRC);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PC4, DDC4, &DDRC);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PC5, DDC5, &DDRC);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PC6, DDC6, &DDRC);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PD0, DDD0, &DDRD);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PD1, DDD1, &DDRD);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PD2, DDD2, &DDRD);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PD3, DDD3, &DDRD);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PD4, DDD4, &DDRD);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PD5, DDD5, &DDRD);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PD6, DDD6, &DDRD);
    RUN_PARAM_TEST(should_define_output, HAL_GPIO_PD7, DDD7, &DDRD);

    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PB0, DDB0, &DDRB);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PB1, DDB1, &DDRB);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PB2, DDB2, &DDRB);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PB3, DDB3, &DDRB);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PB4, DDB4, &DDRB);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PB5, DDB5, &DDRB);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PB6, DDB6, &DDRB);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PB7, DDB7, &DDRB);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PC0, DDC0, &DDRC);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PC1, DDC1, &DDRC);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PC2, DDC2, &DDRC);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PC3, DDC3, &DDRC);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PC4, DDC4, &DDRC);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PC5, DDC5, &DDRC);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PC6, DDC6, &DDRC);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PD0, DDD0, &DDRD);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PD1, DDD1, &DDRD);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PD2, DDD2, &DDRD);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PD3, DDD3, &DDRD);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PD4, DDD4, &DDRD);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PD5, DDD5, &DDRD);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PD6, DDD6, &DDRD);
    RUN_PARAM_TEST(should_define_input, HAL_GPIO_PD7, DDD7, &DDRD);

    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PB0, DDB0, PORTB0, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PB1, DDB1, PORTB1, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PB2, DDB2, PORTB2, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PB3, DDB3, PORTB3, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PB4, DDB4, PORTB4, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PB5, DDB5, PORTB5, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PB6, DDB6, PORTB6, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PB7, DDB7, PORTB7, &DDRB, &PORTB);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PC0, DDC0, PORTC0, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PC1, DDC1, PORTC1, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PC2, DDC2, PORTC2, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PC3, DDC3, PORTC3, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PC4, DDC4, PORTC4, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PC5, DDC5, PORTC5, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PC6, DDC6, PORTC6, &DDRC, &PORTC);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PD0, DDD0, PORTD0, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PD1, DDD1, PORTD1, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PD2, DDD2, PORTD2, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PD3, DDD3, PORTD3, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PD4, DDD4, PORTD4, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PD5, DDD5, PORTD5, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PD6, DDD6, PORTD6, &DDRD, &PORTD);
    RUN_PARAM_TEST(
        should_define_input_pullup, HAL_GPIO_PD7, DDD7, PORTD7, &DDRD, &PORTD);

    RUN_TEST(should_define_many_gpio);

    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PB0, PORTB0, &PORTB);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PB1, PORTB1, &PORTB);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PB2, PORTB2, &PORTB);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PB3, PORTB3, &PORTB);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PB4, PORTB4, &PORTB);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PB5, PORTB5, &PORTB);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PB6, PORTB6, &PORTB);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PB7, PORTB7, &PORTB);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PC0, PORTC0, &PORTC);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PC1, PORTC1, &PORTC);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PC2, PORTC2, &PORTC);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PC3, PORTC3, &PORTC);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PC4, PORTC4, &PORTC);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PC5, PORTC5, &PORTC);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PC6, PORTC6, &PORTC);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PD0, PORTD0, &PORTD);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PD1, PORTD1, &PORTD);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PD2, PORTD2, &PORTD);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PD3, PORTD3, &PORTD);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PD4, PORTD4, &PORTD);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PD5, PORTD5, &PORTD);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PD6, PORTD6, &PORTD);
    RUN_PARAM_TEST(should_set_gpio, HAL_GPIO_PD7, PORTD7, &PORTD);

    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PB0, PORTB0, &PORTB);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PB1, PORTB1, &PORTB);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PB2, PORTB2, &PORTB);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PB3, PORTB3, &PORTB);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PB4, PORTB4, &PORTB);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PB5, PORTB5, &PORTB);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PB6, PORTB6, &PORTB);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PB7, PORTB7, &PORTB);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PC0, PORTC0, &PORTC);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PC1, PORTC1, &PORTC);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PC2, PORTC2, &PORTC);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PC3, PORTC3, &PORTC);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PC4, PORTC4, &PORTC);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PC5, PORTC5, &PORTC);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PC6, PORTC6, &PORTC);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PD0, PORTD0, &PORTD);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PD1, PORTD1, &PORTD);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PD2, PORTD2, &PORTD);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PD3, PORTD3, &PORTD);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PD4, PORTD4, &PORTD);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PD5, PORTD5, &PORTD);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PD6, PORTD6, &PORTD);
    RUN_PARAM_TEST(should_unset_gpio, HAL_GPIO_PD7, PORTD7, &PORTD);

    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PB0, PORTB0, &PORTB);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PB1, PORTB1, &PORTB);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PB2, PORTB2, &PORTB);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PB3, PORTB3, &PORTB);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PB4, PORTB4, &PORTB);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PB5, PORTB5, &PORTB);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PB6, PORTB6, &PORTB);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PB7, PORTB7, &PORTB);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PC0, PORTC0, &PORTC);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PC1, PORTC1, &PORTC);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PC2, PORTC2, &PORTC);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PC3, PORTC3, &PORTC);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PC4, PORTC4, &PORTC);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PC5, PORTC5, &PORTC);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PC6, PORTC6, &PORTC);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PD0, PORTD0, &PORTD);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PD1, PORTD1, &PORTD);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PD2, PORTD2, &PORTD);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PD3, PORTD3, &PORTD);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PD4, PORTD4, &PORTD);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PD5, PORTD5, &PORTD);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PD6, PORTD6, &PORTD);
    RUN_PARAM_TEST(should_toggle_gpio, HAL_GPIO_PD7, PORTD7, &PORTD);

    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB0, BIT(PINB0), HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB0, ~BIT(PINB0), HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB1, BIT(PINB1), HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB1, ~BIT(PINB1), HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB2, BIT(PINB2), HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB2, ~BIT(PINB2), HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB3, BIT(PINB3), HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB3, ~BIT(PINB3), HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB4, BIT(PINB4), HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB4, ~BIT(PINB4), HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB5, BIT(PINB5), HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB5, ~BIT(PINB5), HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB6, BIT(PINB6), HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB6, ~BIT(PINB6), HAL_GPIO_LOW, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB7, BIT(PINB7), HAL_GPIO_HIGH, &PINB);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PB7, ~BIT(PINB7), HAL_GPIO_LOW, &PINB);

    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC0, BIT(PINC0), HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC0, ~BIT(PINC0), HAL_GPIO_LOW, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC1, BIT(PINC1), HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC1, ~BIT(PINC1), HAL_GPIO_LOW, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC2, BIT(PINC2), HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC2, ~BIT(PINC2), HAL_GPIO_LOW, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC3, BIT(PINC3), HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC3, ~BIT(PINC3), HAL_GPIO_LOW, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC4, BIT(PINC4), HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC4, ~BIT(PINC4), HAL_GPIO_LOW, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC5, BIT(PINC5), HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC5, ~BIT(PINC5), HAL_GPIO_LOW, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC6, BIT(PINC6), HAL_GPIO_HIGH, &PINC);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PC6, ~BIT(PINC6), HAL_GPIO_LOW, &PINC);

    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD0, BIT(PIND0), HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD0, ~BIT(PIND0), HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD1, BIT(PIND1), HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD1, ~BIT(PIND1), HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD2, BIT(PIND2), HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD2, ~BIT(PIND2), HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD3, BIT(PIND3), HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD3, ~BIT(PIND3), HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD4, BIT(PIND4), HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD4, ~BIT(PIND4), HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD5, BIT(PIND5), HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD5, ~BIT(PIND5), HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD6, BIT(PIND6), HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD6, ~BIT(PIND6), HAL_GPIO_LOW, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD7, BIT(PIND7), HAL_GPIO_HIGH, &PIND);
    RUN_PARAM_TEST(
        should_read_gpio, HAL_GPIO_PD7, ~BIT(PIND7), HAL_GPIO_LOW, &PIND);

    return UNITY_END();
}