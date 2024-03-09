#include "gpio.h"
#include <avr/io.h>

static volatile uint8_t * const DDRx[] = {
    [HAL_GPIO_REGB] = &DDRB,
    [HAL_GPIO_REGC] = &DDRC,
    [HAL_GPIO_REGD] = &DDRD,
};

volatile uint8_t * const PORTx[] = {
    [HAL_GPIO_REGB] = &PORTB,
    [HAL_GPIO_REGC] = &PORTC,
    [HAL_GPIO_REGD] = &PORTD,
};

volatile uint8_t * const PINx[] = {
    [HAL_GPIO_REGB] = &PINB,
    [HAL_GPIO_REGC] = &PINC,
    [HAL_GPIO_REGD] = &PIND,
};

void
hal_gpio_init(const hal_gpio_def_t *def)
{
    switch (def->dir)
    {
        case HAL_GPIO_INPUT:
            *(DDRx[def->reg]) &= ~(1 << def->pin);
            break;
        case HAL_GPIO_INPUT_WITH_PULLUP:
            *(DDRx[def->reg]) &= ~(1 << def->pin);
            *(PORTx[def->reg]) |= (1 << def->pin);
            break;
        case HAL_GPIO_OUTPUT:
            *(DDRx[def->reg]) |= (1 << def->pin);
            break;
    }
}

void
hal_gpio_init_mask(const hal_gpio_reg_t reg, const uint8_t mask)
{
    *(DDRx[reg]) = mask;
}

void
hal_gpio_toggle(const hal_gpio_def_t *def)
{
    *(PORTx[def->reg]) ^= (1 << def->pin);
}

void
hal_gpio_write(const hal_gpio_def_t *def, const hal_gpio_state_t state)
{
    if (state == HAL_GPIO_HIGH)
    {
        *(PORTx[def->reg]) |= (1 << def->pin);
    }
    else
    {
        *(PORTx[def->reg]) &= ~(1 << def->pin);
    }
}

void
hal_gpio_write_mask(const hal_gpio_reg_t reg, const uint8_t mask)
{
    *(PORTx[reg]) = mask;
}

hal_gpio_state_t
hal_gpio_read(const hal_gpio_def_t *def)
{
    if (*(PINx[def->reg]) & (1 << def->pin))
    {
        return HAL_GPIO_HIGH;
    }
    else
    {
        return HAL_GPIO_LOW;
    }
}
