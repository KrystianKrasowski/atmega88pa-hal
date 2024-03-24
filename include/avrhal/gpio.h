#ifndef _LIBAVRHAL_GPIO_H
#define _LIBAVRHAL_GPIO_H

#include <stdint.h>

typedef enum
{
    HAL_GPIO_INPUT,
    HAL_GPIO_INPUT_WITH_PULLUP,
    HAL_GPIO_OUTPUT
} hal_gpio_direction_t;

typedef enum
{
    HAL_GPIO_REGISTER_B,
    HAL_GPIO_REGISTER_C,
    HAL_GPIO_REGISTER_D
} hal_gpio_register_t;

typedef struct
{
    hal_gpio_register_t  gpio_register;
    hal_gpio_direction_t direction;
    uint8_t              pin;
} hal_gpio_t;

typedef enum
{
    HAL_GPIO_HIGH,
    HAL_GPIO_LOW
} hal_gpio_state_t;

/**
 * @brief Initializes given GPIO definition
 *
 * @param[in] gpio A pioner to the GPIO definition
 */
void
hal_gpio_init(const hal_gpio_t *gpio);

/**
 * @brief Initializes whole AVR GPIO register at once with a given mask
 *
 * @param[in] gpio_register AVR GPIO register
 * @param[in] mask 8-bit mask to write
 */
void
hal_gpio_init_mask(const hal_gpio_register_t gpio_register, const uint8_t mask);

/**
 * @brief Toggles the given GPIO state
 * 
 * @param[in] gpio A pionter to the GPIO definition
 */
void
hal_gpio_toggle(const hal_gpio_t *gpio);

/**
 * @brief Writes new state to the given GPIO
 * 
 * @param[in] gpio A pionter to the GPIO definition
 * @param[in] state A new state to be set on GPIO
 */
void
hal_gpio_write(const hal_gpio_t *gpio, const hal_gpio_state_t state);

/**
 * @brief Writes whole AVR GPIO register at onve with a given mask
 * 
 * @param[in] gpio_register AVR GPIO register
 * @param[in] mask 8-bit mask to write
 */
void
hal_gpio_write_mask(const hal_gpio_register_t gpio_register,
                    const uint8_t             mask);

/**
 * @brief Reads the state of a given GPIO
 * 
 * @param[in] gpio 
 * @return hal_gpio_state_t 
 */
hal_gpio_state_t
hal_gpio_read(const hal_gpio_t *gpio);

#endif
