#ifndef _AVRHAL_GPIOS_H
#define _AVRHAL_GPIOS_H

/**
 * @brief AVR pin representation
 * 
 * PXY - bit X of register Y, ex. PC4 is a 4 indexed bit of DDRC, PORTC or PINC 
 */
typedef enum
{
    HAL_GPIO_PB0,
    HAL_GPIO_PB1,
    HAL_GPIO_PB2,
    HAL_GPIO_PB3,
    HAL_GPIO_PB4,
    HAL_GPIO_PB5,
    HAL_GPIO_PB6,
    HAL_GPIO_PB7,
    HAL_GPIO_PC0,
    HAL_GPIO_PC1,
    HAL_GPIO_PC2,
    HAL_GPIO_PC3,
    HAL_GPIO_PC4,
    HAL_GPIO_PC5,
    HAL_GPIO_PC6,
    HAL_GPIO_PD0,
    HAL_GPIO_PD1,
    HAL_GPIO_PD2,
    HAL_GPIO_PD3,
    HAL_GPIO_PD4,
    HAL_GPIO_PD5,
    HAL_GPIO_PD6,
    HAL_GPIO_PD7,
} hal_gpio_pin_t;

/**
 * @brief GPIO direction mode
 * 
 * Note that INPUT_WITH_PULLUP will set the PORTx bit to logical one. Simple
 * INPUT might require to physically apply pull-up (down) resistor
 */
typedef enum
{
    HAL_GPIO_INPUT,
    HAL_GPIO_INPUT_WITH_PULLUP,
    HAL_GPIO_OUTPUT
} hal_gpio_direction_t;

/**
 * @brief GPIO definition
 */
typedef struct
{
    hal_gpio_pin_t       pin;
    hal_gpio_direction_t direction;
} hal_gpio_t;

/**
 * @brief GPIO state
 */
typedef enum
{
    HAL_GPIO_LOW,
    HAL_GPIO_HIGH,
} hal_gpio_state_t;

/**
 * @brief Sets given GPIO's DDRx register accorging to the specified direction
 * 
 * Note that PORTx might be set as well, if INPUT_WITH_PULLUP direction is 
 * specified for the GPIO. This is an intermediate method - will not affect any 
 * register until hal_gpio_update is called
 * 
 * @param[in] gpio 
 */
void
hal_gpio_define(hal_gpio_t const *gpio);

/**
 * @brief Sets given GPIO's PORTx register according to specified state
 * 
 * This is an intermediate method - will not affect any register until 
 * hal_gpio_update is called
 * 
 * @param[in] gpio 
 * @param[in] state 
 */
void
hal_gpio_set(hal_gpio_t const *gpio, hal_gpio_state_t const state);

/**
 * @brief Toggles given GPIO's PORTx register
 * 
 * This is an intermediate method - will not affect any register until 
 * hal_gpio_update is called
 * 
 * @param[in] gpio 
 */
void
hal_gpio_toggle(hal_gpio_t const *gpio);

/**
 * @brief Updates all DDRx and PORTx registers
 * 
 * This is termination method - all state changes provided with _define, _set
 * and _toggle methods would be applied to DDRx and PORTx registers
 * 
 * @param[in] gpio 
 */
void
hal_gpio_update(void);

/**
 * @brief Reads the state of the given GPIO's PINx register
 * 
 * @param[in] gpio 
 * @return hal_gpio_state_t 
 */
hal_gpio_state_t
hal_gpio_read(hal_gpio_t const *gpio);

#endif