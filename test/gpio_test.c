#include "gpio.h"
#include "unity_config.h"
#include <unity/unity.h>

uint8_t DDRB = 0;
uint8_t DDRC = 0;
uint8_t DDRD = 0;

uint8_t PORTB = 0;
uint8_t PORTC = 0;
uint8_t PORTD = 0;

uint8_t PINB = 0;
uint8_t PINC = 0;
uint8_t PIND = 0;

void
should_define_gpio_as_output(hal_gpio_reg_t reg,
                             uint8_t        pin_no,
                             uint8_t       *avr_ddr,
                             uint8_t        expected_mask)
{
    // given
    *avr_ddr           = 0;
    hal_gpio_def_t def = {.dir = HAL_GPIO_OUTPUT, .reg = reg, .pin = pin_no};

    // when
    hal_gpio_init(&def);

    // then
    TEST_ASSERT_EQUAL_HEX8(expected_mask, *avr_ddr);
}
void
should_define_gpio_as_input(hal_gpio_reg_t reg,
                            uint8_t        pin_no,
                            uint8_t       *avr_ddr,
                            uint8_t        expected_mask)
{
    // given
    *avr_ddr           = 0xff;
    hal_gpio_def_t def = {.dir = HAL_GPIO_INPUT, .reg = reg, .pin = pin_no};

    // when
    hal_gpio_init(&def);

    // then
    TEST_ASSERT_EQUAL_HEX8(expected_mask, *avr_ddr);
}

void
should_toggle_gpio(hal_gpio_reg_t reg,
                   uint8_t        pin_no,
                   uint8_t       *avr_port,
                   uint8_t        expected_mask)
{
    // given
    *avr_port          = 0;
    hal_gpio_def_t def = {.dir = HAL_GPIO_OUTPUT, .reg = reg, .pin = pin_no};

    // when
    hal_gpio_toggle(&def);

    // then
    TEST_ASSERT_EQUAL_HEX8(expected_mask, *avr_port);
}

void
should_write_gpio(hal_gpio_reg_t reg,
                  uint8_t        pin_no,
                  uint8_t       *avr_port,
                  uint8_t        expected_high_mask)
{
    // given
    *avr_port          = 0;
    hal_gpio_def_t def = {.dir = HAL_GPIO_OUTPUT, .reg = reg, .pin = pin_no};

    // when
    hal_gpio_write(&def, HAL_GPIO_HIGH);
    uint8_t actual_when_high = *avr_port;
    hal_gpio_write(&def, HAL_GPIO_LOW);
    uint8_t actual_when_low = *avr_port;

    // then
    TEST_ASSERT_EQUAL_HEX8(expected_high_mask, actual_when_high);
    TEST_ASSERT_EQUAL_HEX8(0x00, actual_when_low);
}
void
should_read_gpio(hal_gpio_reg_t   reg,
                 uint8_t          pin_no,
                 uint8_t          avr_pin_value,
                 uint8_t         *avr_pin,
                 hal_gpio_state_t expected_state)
{
    // given
    *avr_pin           = avr_pin_value;
    hal_gpio_def_t def = {.dir = HAL_GPIO_INPUT, .reg = reg, .pin = pin_no};

    // when
    hal_gpio_state_t actual = hal_gpio_read(&def);

    // then
    TEST_ASSERT_EQUAL(expected_state, actual);
}

void
setUp()
{
    uint8_t DDRB  = 0;
    uint8_t DDRC  = 0;
    uint8_t DDRD  = 0;
    uint8_t PORTB = 0;
    uint8_t PORTC = 0;
    uint8_t PORTD = 0;
    uint8_t PINB  = 0;
    uint8_t PINC  = 0;
    uint8_t PIND  = 0;
}

void
tearDown()
{
}

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGB, 0, &DDRB, 0x01);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGB, 1, &DDRB, 0x02);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGB, 2, &DDRB, 0x04);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGB, 3, &DDRB, 0x08);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGB, 4, &DDRB, 0x10);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGB, 5, &DDRB, 0x20);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGB, 6, &DDRB, 0x40);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGB, 7, &DDRB, 0x80);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGC, 0, &DDRC, 0x01);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGC, 1, &DDRC, 0x02);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGC, 2, &DDRC, 0x04);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGC, 3, &DDRC, 0x08);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGC, 4, &DDRC, 0x10);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGC, 5, &DDRC, 0x20);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGC, 6, &DDRC, 0x40);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGC, 7, &DDRC, 0x80);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGD, 0, &DDRD, 0x01);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGD, 1, &DDRD, 0x02);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGD, 2, &DDRD, 0x04);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGD, 3, &DDRD, 0x08);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGD, 4, &DDRD, 0x10);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGD, 5, &DDRD, 0x20);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGD, 6, &DDRD, 0x40);
    RUN_TEST(should_define_gpio_as_output, HAL_GPIO_REGD, 7, &DDRD, 0x80);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGB, 0, &DDRB, 0xfe);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGB, 1, &DDRB, 0xfd);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGB, 2, &DDRB, 0xfb);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGB, 3, &DDRB, 0xf7);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGB, 4, &DDRB, 0xef);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGB, 5, &DDRB, 0xdf);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGB, 6, &DDRB, 0xbf);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGB, 7, &DDRB, 0x7f);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGC, 0, &DDRC, 0xfe);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGC, 1, &DDRC, 0xfd);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGC, 2, &DDRC, 0xfb);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGC, 3, &DDRC, 0xf7);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGC, 4, &DDRC, 0xef);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGC, 5, &DDRC, 0xdf);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGC, 6, &DDRC, 0xbf);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGC, 7, &DDRC, 0x7f);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGD, 0, &DDRD, 0xfe);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGD, 1, &DDRD, 0xfd);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGD, 2, &DDRD, 0xfb);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGD, 3, &DDRD, 0xf7);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGD, 4, &DDRD, 0xef);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGD, 5, &DDRD, 0xdf);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGD, 6, &DDRD, 0xbf);
    RUN_TEST(should_define_gpio_as_input, HAL_GPIO_REGD, 7, &DDRD, 0x7f);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGB, 0, &PORTB, 0x01);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGB, 1, &PORTB, 0x02);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGB, 2, &PORTB, 0x04);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGB, 3, &PORTB, 0x08);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGB, 4, &PORTB, 0x10);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGB, 5, &PORTB, 0x20);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGB, 6, &PORTB, 0x40);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGB, 7, &PORTB, 0x80);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGC, 0, &PORTC, 0x01);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGC, 1, &PORTC, 0x02);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGC, 2, &PORTC, 0x04);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGC, 3, &PORTC, 0x08);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGC, 4, &PORTC, 0x10);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGC, 5, &PORTC, 0x20);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGC, 6, &PORTC, 0x40);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGC, 7, &PORTC, 0x80);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGD, 0, &PORTD, 0x01);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGD, 1, &PORTD, 0x02);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGD, 2, &PORTD, 0x04);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGD, 3, &PORTD, 0x08);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGD, 4, &PORTD, 0x10);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGD, 5, &PORTD, 0x20);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGD, 6, &PORTD, 0x40);
    RUN_TEST(should_toggle_gpio, HAL_GPIO_REGD, 7, &PORTD, 0x80);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGB, 0, &PORTB, 0x01);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGB, 1, &PORTB, 0x02);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGB, 2, &PORTB, 0x04);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGB, 3, &PORTB, 0x08);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGB, 4, &PORTB, 0x10);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGB, 5, &PORTB, 0x20);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGB, 6, &PORTB, 0x40);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGB, 7, &PORTB, 0x80);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGC, 0, &PORTC, 0x01);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGC, 1, &PORTC, 0x02);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGC, 2, &PORTC, 0x04);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGC, 3, &PORTC, 0x08);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGC, 4, &PORTC, 0x10);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGC, 5, &PORTC, 0x20);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGC, 6, &PORTC, 0x40);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGC, 7, &PORTC, 0x80);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGD, 0, &PORTD, 0x01);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGD, 1, &PORTD, 0x02);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGD, 2, &PORTD, 0x04);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGD, 3, &PORTD, 0x08);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGD, 4, &PORTD, 0x10);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGD, 5, &PORTD, 0x20);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGD, 6, &PORTD, 0x40);
    RUN_TEST(should_write_gpio, HAL_GPIO_REGD, 7, &PORTD, 0x80);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 0, 0x01, &PINB, HAL_GPIO_HIGH);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 0, 0xFE, &PINB, HAL_GPIO_LOW);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 1, 0x02, &PINB, HAL_GPIO_HIGH);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 1, 0xFD, &PINB, HAL_GPIO_LOW);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 2, 0x04, &PINB, HAL_GPIO_HIGH);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 2, 0xFB, &PINB, HAL_GPIO_LOW);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 3, 0x08, &PINB, HAL_GPIO_HIGH);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 3, 0xF7, &PINB, HAL_GPIO_LOW);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 4, 0x10, &PINB, HAL_GPIO_HIGH);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 4, 0xEF, &PINB, HAL_GPIO_LOW);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 5, 0x20, &PINB, HAL_GPIO_HIGH);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 5, 0xDF, &PINB, HAL_GPIO_LOW);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 6, 0x40, &PINB, HAL_GPIO_HIGH);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 6, 0xBF, &PINB, HAL_GPIO_LOW);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 7, 0x80, &PINB, HAL_GPIO_HIGH);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGB, 7, 0x7F, &PINB, HAL_GPIO_LOW);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGC, 0, 0x01, &PINC, HAL_GPIO_HIGH);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGC, 0, 0xFE, &PINC, HAL_GPIO_LOW);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGC, 1, 0x02, &PINC, HAL_GPIO_HIGH);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGC, 1, 0xFD, &PINC, HAL_GPIO_LOW);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGC, 2, 0x04, &PINC, HAL_GPIO_HIGH);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGC, 2, 0xFB, &PINC, HAL_GPIO_LOW);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGC, 3, 0x08, &PINC, HAL_GPIO_HIGH);
    RUN_TEST(should_read_gpio, HAL_GPIO_REGC, 3, 0xF7, &PINC, HAL_GPIO_LOW);
    return UNITY_END();
}
