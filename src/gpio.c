#include "gpio.h"

volatile uint8_t *const DDRx[] = {&DDRB, &DDRC, &DDRD};
volatile uint8_t *const PORTx[] = {&PORTB, &PORTC, &PORTD};
volatile uint8_t *const PINx[] = {&PINB, &PINC, &PIND};

void hal_gpio_init(hal_gpio_def_t def)
{
  switch (def.dir)
  {
    case HAL_GPIO_INPUT:
      *(DDRx[def.reg]) &= ~(1 << def.pin);
      break;
    case HAL_GPIO_INPUT_WITH_PULLUP:
      *(DDRx[def.reg]) &= ~(1 << def.pin);
      *(PORTx[def.reg]) |= (1 << def.pin);
      break;
    case HAL_GPIO_OUTPUT:
      *(DDRx[def.reg]) |= (1 << def.pin);
      break;
  }
}

void hal_gpio_toggle(hal_gpio_def_t def)
{
  *(PORTx[def.reg]) ^= (1 << def.pin);
}

void hal_gpio_write(hal_gpio_def_t def, hal_gpio_state_t state)
{
  if (state == HAL_GPIO_HIGH)
  {
    *(PORTx[def.reg]) |= (1 << def.pin);
  }
  else
  {
    *(PORTx[def.reg]) &= ~(1 << def.pin);
  }
}

hal_gpio_state_t hal_gpio_read(hal_gpio_def_t def)
{
  if (*(PINx[def.reg]) & (1 << def.pin))
  {
    return HAL_GPIO_HIGH;
  }
  else
  {
    return HAL_GPIO_LOW;
  }
}