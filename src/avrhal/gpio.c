#include "avrhal/gpio.h"
#include <avr/io.h>

#define DDRx(pin)      *(DDRx[REGISTER_MAP[pin]])
#define PORTx(pin)     *(PORTx[REGISTER_MAP[pin]])
#define PINx(pin)      *(PINx[REGISTER_MAP[pin]])
#define PIN_INDEX(pin) PIN_MAP[pin]

static hal_gpio_register_t const REGISTER_MAP[] = {
    [HAL_GPIO_PB0] = HAL_GPIO_REGISTER_B, [HAL_GPIO_PB1] = HAL_GPIO_REGISTER_B,
    [HAL_GPIO_PB2] = HAL_GPIO_REGISTER_B, [HAL_GPIO_PB3] = HAL_GPIO_REGISTER_B,
    [HAL_GPIO_PB4] = HAL_GPIO_REGISTER_B, [HAL_GPIO_PB5] = HAL_GPIO_REGISTER_B,
    [HAL_GPIO_PB6] = HAL_GPIO_REGISTER_B, [HAL_GPIO_PB7] = HAL_GPIO_REGISTER_B,
    [HAL_GPIO_PC0] = HAL_GPIO_REGISTER_C, [HAL_GPIO_PC1] = HAL_GPIO_REGISTER_C,
    [HAL_GPIO_PC2] = HAL_GPIO_REGISTER_C, [HAL_GPIO_PC3] = HAL_GPIO_REGISTER_C,
    [HAL_GPIO_PC4] = HAL_GPIO_REGISTER_C, [HAL_GPIO_PC5] = HAL_GPIO_REGISTER_C,
    [HAL_GPIO_PC6] = HAL_GPIO_REGISTER_C, [HAL_GPIO_PD0] = HAL_GPIO_REGISTER_D,
    [HAL_GPIO_PD1] = HAL_GPIO_REGISTER_D, [HAL_GPIO_PD2] = HAL_GPIO_REGISTER_D,
    [HAL_GPIO_PD3] = HAL_GPIO_REGISTER_D, [HAL_GPIO_PD4] = HAL_GPIO_REGISTER_D,
    [HAL_GPIO_PD5] = HAL_GPIO_REGISTER_D, [HAL_GPIO_PD6] = HAL_GPIO_REGISTER_D,
    [HAL_GPIO_PD7] = HAL_GPIO_REGISTER_D,
};

static volatile uint8_t * const DDRx[] = {
    [HAL_GPIO_REGISTER_B] = &DDRB,
    [HAL_GPIO_REGISTER_C] = &DDRC,
    [HAL_GPIO_REGISTER_D] = &DDRD,
};

static volatile uint8_t * const PORTx[] = {
    [HAL_GPIO_REGISTER_B] = &PORTB,
    [HAL_GPIO_REGISTER_C] = &PORTC,
    [HAL_GPIO_REGISTER_D] = &PORTD,
};

static volatile uint8_t * const PINx[] = {
    [HAL_GPIO_REGISTER_B] = &PINB,
    [HAL_GPIO_REGISTER_C] = &PINC,
    [HAL_GPIO_REGISTER_D] = &PIND,
};

static uint8_t const PIN_MAP[] = {
    [HAL_GPIO_PB0] = 0, [HAL_GPIO_PB1] = 1, [HAL_GPIO_PB2] = 2,
    [HAL_GPIO_PB3] = 3, [HAL_GPIO_PB4] = 4, [HAL_GPIO_PB5] = 5,
    [HAL_GPIO_PB6] = 6, [HAL_GPIO_PB7] = 7, [HAL_GPIO_PC0] = 0,
    [HAL_GPIO_PC1] = 1, [HAL_GPIO_PC2] = 2, [HAL_GPIO_PC3] = 3,
    [HAL_GPIO_PC4] = 4, [HAL_GPIO_PC5] = 5, [HAL_GPIO_PC6] = 6,
    [HAL_GPIO_PD0] = 0, [HAL_GPIO_PD1] = 1, [HAL_GPIO_PD2] = 2,
    [HAL_GPIO_PD3] = 3, [HAL_GPIO_PD4] = 4, [HAL_GPIO_PD5] = 5,
    [HAL_GPIO_PD6] = 6, [HAL_GPIO_PD7] = 7,
};

void
hal_gpio_init(const hal_gpio_t *gpio)
{
    switch (gpio->direction)
    {
        case HAL_GPIO_INPUT:
            DDRx(gpio->pin) &= ~(1 << PIN_INDEX(gpio->pin));
            break;
        case HAL_GPIO_INPUT_WITH_PULLUP:
            DDRx(gpio->pin) &= ~(1 << PIN_INDEX(gpio->pin));
            PORTx(gpio->pin) |= (1 << PIN_INDEX(gpio->pin));
            break;
        case HAL_GPIO_OUTPUT:
            DDRx(gpio->pin) |= (1 << PIN_INDEX(gpio->pin));
            break;
    }
}

void
hal_gpio_init_mask(const hal_gpio_register_t gpio_register, const uint8_t mask)
{
    *(DDRx[gpio_register]) = mask;
}

void
hal_gpio_toggle(const hal_gpio_t *gpio)
{
    PORTx(gpio->pin) ^= (1 << PIN_INDEX(gpio->pin));
}

void
hal_gpio_write(const hal_gpio_t *gpio, const hal_gpio_state_t state)
{
    if (state == HAL_GPIO_HIGH)
    {
        PORTx(gpio->pin) |= (1 << PIN_INDEX(gpio->pin));
    }
    else
    {
        PORTx(gpio->pin) &= ~(1 << PIN_INDEX(gpio->pin));
    }
}

void
hal_gpio_write_mask(const hal_gpio_register_t gpio_register, const uint8_t mask)
{
    *(PORTx[gpio_register]) = mask;
}

hal_gpio_state_t
hal_gpio_read(const hal_gpio_t *gpio)
{
    if (PINx(gpio->pin) & (1 << PIN_INDEX(gpio->pin)))
    {
        return HAL_GPIO_HIGH;
    }
    else
    {
        return HAL_GPIO_LOW;
    }
}

hal_gpio_register_t
hal_gpio_get_register(const hal_gpio_pin_t pin)
{
    return REGISTER_MAP[pin];
}

uint8_t
hal_gpio_get_index(const hal_gpio_pin_t pin)
{
    return PIN_INDEX(pin);
}