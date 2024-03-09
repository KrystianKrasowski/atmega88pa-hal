#ifndef _LIBAVRHAL_GPIO
#define _LIBAVRHAL_GPIO

#include <stdint.h>

typedef enum
{
    HAL_GPIO_INPUT,
    HAL_GPIO_INPUT_WITH_PULLUP,
    HAL_GPIO_OUTPUT
} hal_gpio_dir_t;

typedef enum
{
    HAL_GPIO_REGB,
    HAL_GPIO_REGC,
    HAL_GPIO_REGD
} hal_gpio_reg_t;

typedef struct
{
    hal_gpio_reg_t reg;
    hal_gpio_dir_t dir;
    uint8_t        pin;
} hal_gpio_def_t;

typedef enum
{
    HAL_GPIO_HIGH,
    HAL_GPIO_LOW
} hal_gpio_state_t;

void
hal_gpio_init(const hal_gpio_def_t *def);

void
hal_gpio_init_mask(const hal_gpio_reg_t reg, const uint8_t mask);

void
hal_gpio_toggle(const hal_gpio_def_t *def);

void
hal_gpio_write(const hal_gpio_def_t *def, const hal_gpio_state_t state);

void
hal_gpio_write_mask(const hal_gpio_reg_t reg, const uint8_t mask);

hal_gpio_state_t
hal_gpio_read(const hal_gpio_def_t *def);

#endif
