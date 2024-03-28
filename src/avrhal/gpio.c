#include "avrhal/gpio.h"
#include <avr/io.h>

static volatile uint8_t * const DDRx[] = {
    [HAL_GPIO_PB0] = &DDRB, [HAL_GPIO_PB1] = &DDRB, [HAL_GPIO_PB2] = &DDRB,
    [HAL_GPIO_PB3] = &DDRB, [HAL_GPIO_PB4] = &DDRB, [HAL_GPIO_PB5] = &DDRB,
    [HAL_GPIO_PB6] = &DDRB, [HAL_GPIO_PB7] = &DDRB, [HAL_GPIO_PC0] = &DDRC,
    [HAL_GPIO_PC1] = &DDRC, [HAL_GPIO_PC2] = &DDRC, [HAL_GPIO_PC3] = &DDRC,
    [HAL_GPIO_PC4] = &DDRC, [HAL_GPIO_PC5] = &DDRC, [HAL_GPIO_PC6] = &DDRC,
    [HAL_GPIO_PD0] = &DDRD, [HAL_GPIO_PD1] = &DDRD, [HAL_GPIO_PD2] = &DDRD,
    [HAL_GPIO_PD3] = &DDRD, [HAL_GPIO_PD4] = &DDRD, [HAL_GPIO_PD5] = &DDRD,
    [HAL_GPIO_PD6] = &DDRD, [HAL_GPIO_PD7] = &DDRD,
};

static volatile uint8_t * const PORTx[] = {
    [HAL_GPIO_PB0] = &PORTB, [HAL_GPIO_PB1] = &PORTB, [HAL_GPIO_PB2] = &PORTB,
    [HAL_GPIO_PB3] = &PORTB, [HAL_GPIO_PB4] = &PORTB, [HAL_GPIO_PB5] = &PORTB,
    [HAL_GPIO_PB6] = &PORTB, [HAL_GPIO_PB7] = &PORTB, [HAL_GPIO_PC0] = &PORTC,
    [HAL_GPIO_PC1] = &PORTC, [HAL_GPIO_PC2] = &PORTC, [HAL_GPIO_PC3] = &PORTC,
    [HAL_GPIO_PC4] = &PORTC, [HAL_GPIO_PC5] = &PORTC, [HAL_GPIO_PC6] = &PORTC,
    [HAL_GPIO_PD0] = &PORTD, [HAL_GPIO_PD1] = &PORTD, [HAL_GPIO_PD2] = &PORTD,
    [HAL_GPIO_PD3] = &PORTD, [HAL_GPIO_PD4] = &PORTD, [HAL_GPIO_PD5] = &PORTD,
    [HAL_GPIO_PD6] = &PORTD, [HAL_GPIO_PD7] = &PORTD,
};

static volatile uint8_t * const PINx[] = {
    [HAL_GPIO_PB0] = &PINB, [HAL_GPIO_PB1] = &PINB, [HAL_GPIO_PB2] = &PINB,
    [HAL_GPIO_PB3] = &PINB, [HAL_GPIO_PB4] = &PINB, [HAL_GPIO_PB5] = &PINB,
    [HAL_GPIO_PB6] = &PINB, [HAL_GPIO_PB7] = &PINB, [HAL_GPIO_PC0] = &PINC,
    [HAL_GPIO_PC1] = &PINC, [HAL_GPIO_PC2] = &PINC, [HAL_GPIO_PC3] = &PINC,
    [HAL_GPIO_PC4] = &PINC, [HAL_GPIO_PC5] = &PINC, [HAL_GPIO_PC6] = &PINC,
    [HAL_GPIO_PD0] = &PIND, [HAL_GPIO_PD1] = &PIND, [HAL_GPIO_PD2] = &PIND,
    [HAL_GPIO_PD3] = &PIND, [HAL_GPIO_PD4] = &PIND, [HAL_GPIO_PD5] = &PIND,
    [HAL_GPIO_PD6] = &PIND, [HAL_GPIO_PD7] = &PIND,
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
            *(DDRx[gpio->pin]) &= ~(1 << PIN_MAP[gpio->pin]);
            break;
        case HAL_GPIO_INPUT_WITH_PULLUP:
            *(DDRx[gpio->pin]) &= ~(1 << PIN_MAP[gpio->pin]);
            *(PORTx[gpio->pin]) |= (1 << PIN_MAP[gpio->pin]);
            break;
        case HAL_GPIO_OUTPUT:
            *(DDRx[gpio->pin]) |= (1 << PIN_MAP[gpio->pin]);
            break;
    }
}

void
hal_gpio_init_mask(const hal_gpio_register_t gpio_register, const uint8_t mask)
{
    switch (gpio_register)
    {
        case HAL_GPIO_REGISTER_B:
            DDRB = mask;
            break;
        case HAL_GPIO_REGISTER_C:
            DDRC = mask;
            break;
        case HAL_GPIO_REGISTER_D:
            DDRD = mask;
            break;
    }
}

void
hal_gpio_toggle(const hal_gpio_t *gpio)
{
    *(PORTx[gpio->pin]) ^= (1 << PIN_MAP[gpio->pin]);
}

void
hal_gpio_write(const hal_gpio_t *gpio, const hal_gpio_state_t state)
{
    if (state == HAL_GPIO_HIGH)
    {
        *(PORTx[gpio->pin]) |= (1 << PIN_MAP[gpio->pin]);
    }
    else
    {
        *(PORTx[gpio->pin]) &= ~(1 << PIN_MAP[gpio->pin]);
    }
}

void
hal_gpio_write_mask(const hal_gpio_register_t gpio_register, const uint8_t mask)
{
    switch (gpio_register)
    {
        case HAL_GPIO_REGISTER_B:
            PORTB = mask;
            break;
        case HAL_GPIO_REGISTER_C:
            PORTC = mask;
            break;
        case HAL_GPIO_REGISTER_D:
            PORTD = mask;
            break;
    }
}

hal_gpio_state_t
hal_gpio_read(const hal_gpio_t *gpio)
{
    if (*(PINx[gpio->pin]) & (1 << PIN_MAP[gpio->pin]))
    {
        return HAL_GPIO_HIGH;
    }
    else
    {
        return HAL_GPIO_LOW;
    }
}
