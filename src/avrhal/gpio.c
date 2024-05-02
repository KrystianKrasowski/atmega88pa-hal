#include <avrhal/gpio.h>
#include <avr/io.h>

#define DDRX_BUFFER(pin)  *(GPIO_MAP[pin].ddrx_buffer)
#define PORTX_BUFFER(pin) *(GPIO_MAP[pin].portx_buffer)
#define PINX(pin)         *(GPIO_MAP[pin].pinx)
#define BIT_INDEX(pin)    GPIO_MAP[pin].bit_index

typedef struct
{
    uint8_t * const          ddrx_buffer;
    uint8_t * const          portx_buffer;
    uint8_t volatile * const pinx;
    uint8_t const            bit_index;
} hal_gpios_map_t;

uint8_t static ddrb_buffer  = 0;
uint8_t static ddrc_buffer  = 0;
uint8_t static ddrd_buffer  = 0;
uint8_t static portb_buffer = 0;
uint8_t static portc_buffer = 0;
uint8_t static portd_buffer = 0;

hal_gpios_map_t static GPIO_MAP[] = {
    [HAL_GPIO_PB0] = {&ddrb_buffer, &portb_buffer, &PINB, 0},
    [HAL_GPIO_PB1] = {&ddrb_buffer, &portb_buffer, &PINB, 1},
    [HAL_GPIO_PB2] = {&ddrb_buffer, &portb_buffer, &PINB, 2},
    [HAL_GPIO_PB3] = {&ddrb_buffer, &portb_buffer, &PINB, 3},
    [HAL_GPIO_PB4] = {&ddrb_buffer, &portb_buffer, &PINB, 4},
    [HAL_GPIO_PB5] = {&ddrb_buffer, &portb_buffer, &PINB, 5},
    [HAL_GPIO_PB6] = {&ddrb_buffer, &portb_buffer, &PINB, 6},
    [HAL_GPIO_PB7] = {&ddrb_buffer, &portb_buffer, &PINB, 7},
    [HAL_GPIO_PC0] = {&ddrc_buffer, &portc_buffer, &PINC, 0},
    [HAL_GPIO_PC1] = {&ddrc_buffer, &portc_buffer, &PINC, 1},
    [HAL_GPIO_PC2] = {&ddrc_buffer, &portc_buffer, &PINC, 2},
    [HAL_GPIO_PC3] = {&ddrc_buffer, &portc_buffer, &PINC, 3},
    [HAL_GPIO_PC4] = {&ddrc_buffer, &portc_buffer, &PINC, 4},
    [HAL_GPIO_PC5] = {&ddrc_buffer, &portc_buffer, &PINC, 5},
    [HAL_GPIO_PC6] = {&ddrc_buffer, &portc_buffer, &PINC, 6},
    [HAL_GPIO_PD0] = {&ddrd_buffer, &portd_buffer, &PIND, 0},
    [HAL_GPIO_PD1] = {&ddrd_buffer, &portd_buffer, &PIND, 1},
    [HAL_GPIO_PD2] = {&ddrd_buffer, &portd_buffer, &PIND, 2},
    [HAL_GPIO_PD3] = {&ddrd_buffer, &portd_buffer, &PIND, 3},
    [HAL_GPIO_PD4] = {&ddrd_buffer, &portd_buffer, &PIND, 4},
    [HAL_GPIO_PD5] = {&ddrd_buffer, &portd_buffer, &PIND, 5},
    [HAL_GPIO_PD6] = {&ddrd_buffer, &portd_buffer, &PIND, 6},
    [HAL_GPIO_PD7] = {&ddrd_buffer, &portd_buffer, &PIND, 7},
};

void
hal_gpio_define(hal_gpio_t const *gpio)
{
    switch (gpio->direction)
    {
        case HAL_GPIO_OUTPUT:
            DDRX_BUFFER(gpio->pin) |= (1 << BIT_INDEX(gpio->pin));
            PORTX_BUFFER(gpio->pin) &= ~(1 << BIT_INDEX(gpio->pin));
            break;
        case HAL_GPIO_INPUT_WITH_PULLUP:
            DDRX_BUFFER(gpio->pin) &= ~(1 << BIT_INDEX(gpio->pin));
            PORTX_BUFFER(gpio->pin) |= (1 << BIT_INDEX(gpio->pin));
            break;
        case HAL_GPIO_INPUT:
        default:
            DDRX_BUFFER(gpio->pin) &= ~(1 << BIT_INDEX(gpio->pin));
            PORTX_BUFFER(gpio->pin) &= ~(1 << BIT_INDEX(gpio->pin));
    }
}

void
hal_gpio_set(hal_gpio_t const *gpio, hal_gpio_state_t const state)
{
    if (state == HAL_GPIO_LOW)
    {
        PORTX_BUFFER(gpio->pin) &= ~(1 << BIT_INDEX(gpio->pin));
    }
    else
    {
        PORTX_BUFFER(gpio->pin) |= (1 << BIT_INDEX(gpio->pin));
    }
}

void
hal_gpio_toggle(hal_gpio_t const *gpio)
{
    PORTX_BUFFER(gpio->pin) ^= (1 << BIT_INDEX(gpio->pin));
}

hal_gpio_state_t
hal_gpio_read(hal_gpio_t const *gpio)
{
    if (!(PINX(gpio->pin) & (1 << BIT_INDEX(gpio->pin))))
    {
        return HAL_GPIO_LOW;
    }
    else
    {
        return HAL_GPIO_HIGH;
    }
}

void
hal_gpio_update(void)
{
    DDRB  = ddrb_buffer;
    DDRC  = ddrc_buffer;
    DDRD  = ddrd_buffer;
    PORTB = portb_buffer;
    PORTC = portc_buffer;
    PORTD = portd_buffer;
}