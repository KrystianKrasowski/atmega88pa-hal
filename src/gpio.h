#ifndef _LIBAVRHAL
#define _LIBAVRHAL

#include <stdint.h>

typedef enum {
  HAL_GPIO_INPUT,
  HAL_GPIO_INPUT_WITH_PULLUP,
  HAL_GPIO_OUTPUT
} hal_gpio_dir;

typedef enum {
  HAL_GPIO_REGB,
  HAL_GPIO_REGC,
  HAL_GPIO_REGD
} hal_gpio_reg;

typedef struct {
  uint8_t reg;
  hal_gpio_dir dir;
  uint8_t pin;
} hal_gpio_def;

typedef enum {
  HAL_GPIO_HIGH,
  HAL_GPIO_LOW
} hal_gpio_state;

void hal_gpio_init(hal_gpio_def def);
void hal_gpio_toggle(hal_gpio_def def);
void hal_gpio_write(hal_gpio_def def, hal_gpio_state state);
hal_gpio_state hal_gpio_read(hal_gpio_def def);

#endif