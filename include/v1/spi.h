#include <stdint.h>

typedef enum
{
    HAL_SPI_BIT_ORDER_MSB_FIRST,
    HAL_SPI_BIT_ORDER_LSB_FIRST
} hal_spi_bit_order_t;

typedef enum
{
    HAL_SPI_CLOCK_POLARITY_RISING_FALLING,
    HAL_SPI_CLOCK_POLARITY_FALLING_RISING
} hal_spi_clock_polarity_t;

typedef enum
{
    HAL_SPI_CLOCK_PHASE_SAMPLE_SETUP,
    HAL_SPI_CLOCK_PHASE_SETUP_SAMPLE,
} hal_spi_clock_phase_t;

typedef enum
{
    HAL_SPI_PRESCALLER_2,
    HAL_SPI_PRESCALLER_4,
    HAL_SPI_PRESCALLER_8,
    HAL_SPI_PRESCALLER_16,
    HAL_SPI_PRESCALLER_32,
    HAL_SPI_PRESCALLER_64,
    HAL_SPI_PRESCALLER_128,
} hal_spi_prescaller_t;

typedef struct
{
    uint8_t                  interrupts;
    hal_spi_bit_order_t      order;
    hal_spi_clock_polarity_t cpol;
    hal_spi_clock_phase_t    cpha;
    hal_spi_prescaller_t     presc;
} hal_spi_def_t;

void
hal_spi_master_init(const hal_spi_def_t *def);

uint8_t
hal_spi_master_transmit_receive(const uint8_t chr);

void
hal_spi_master_transmit(const uint8_t chr);

__attribute__((weak)) void
hal_spi_on_transfer_complete(const uint8_t chr);
