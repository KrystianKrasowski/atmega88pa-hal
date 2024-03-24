#include "avrhal/gpio.h"
#include <avr/io.h>

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

void
hal_gpio_init(const hal_gpio_t *def)
{
    switch (def->direction)
    {
        case HAL_GPIO_INPUT:
            *(DDRx[def->gpio_register]) &= ~(1 << def->pin);
            break;
        case HAL_GPIO_INPUT_WITH_PULLUP:
            *(DDRx[def->gpio_register]) &= ~(1 << def->pin);
            *(PORTx[def->gpio_register]) |= (1 << def->pin);
            break;
        case HAL_GPIO_OUTPUT:
            *(DDRx[def->gpio_register]) |= (1 << def->pin);
            break;
    }
}

void
hal_gpio_init_mask(const hal_gpio_register_t gpio_register, const uint8_t mask)
{
    *(DDRx[gpio_register]) = mask;
}

void
hal_gpio_toggle(const hal_gpio_t *def)
{
    *(PORTx[def->gpio_register]) ^= (1 << def->pin);
}

void
hal_gpio_write(const hal_gpio_t *def, const hal_gpio_state_t state)
{
    if (state == HAL_GPIO_HIGH)
    {
        *(PORTx[def->gpio_register]) |= (1 << def->pin);
    }
    else
    {
        *(PORTx[def->gpio_register]) &= ~(1 << def->pin);
    }
}

void
hal_gpio_write_mask(const hal_gpio_register_t gpio_register, const uint8_t mask)
{
    *(PORTx[gpio_register]) = mask;
}

hal_gpio_state_t
hal_gpio_read(const hal_gpio_t *def)
{
    if (*(PINx[def->gpio_register]) & (1 << def->pin))
    {
        return HAL_GPIO_HIGH;
    }
    else
    {
        return HAL_GPIO_LOW;
    }
}
