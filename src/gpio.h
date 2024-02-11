#ifndef _LIBAVRHAL
#define _LIBAVRHAL

#include <avr/io.h>

typedef enum {
  HAL_GPIO_INPUT,
  HAL_GPIO_INPUT_WITH_PULLUP,
  HAL_GPIO_OUTPUT
} hal_gpio_dir_t;

typedef enum {
  HAL_GPIO_REGB,
  HAL_GPIO_REGC,
  HAL_GPIO_REGD
} hal_gpio_reg_t;

typedef struct {
  uint8_t reg;
  hal_gpio_dir_t dir;
  uint8_t pin;
} hal_gpio_def_t;

typedef enum {
  HAL_GPIO_HIGH,
  HAL_GPIO_LOW
} hal_gpio_state_t;

void hal_gpio_init(hal_gpio_def_t def);
void hal_gpio_toggle(hal_gpio_def_t def);
void hal_gpio_write(hal_gpio_def_t def, hal_gpio_state_t state);
hal_gpio_state_t hal_gpio_read(hal_gpio_def_t def);

#endif