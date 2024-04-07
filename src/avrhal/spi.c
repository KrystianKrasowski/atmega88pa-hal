#include "avrhal/spi.h"
#include "avrhal/gpio.h"
#include <avr/interrupt.h>
#include <avr/io.h>

hal_gpio_t static slave_select = {HAL_GPIO_PB2, HAL_GPIO_INPUT_WITH_PULLUP};
hal_gpio_t static mosi         = {HAL_GPIO_PB3, HAL_GPIO_OUTPUT};
hal_gpio_t static sck          = {HAL_GPIO_PB5, HAL_GPIO_OUTPUT};

void
hal_spi_master_init(hal_spi_t const *spi)
{
    // This is necessary to maintain uC in SPI master mode
    hal_gpio_define(&slave_select);
    hal_gpio_define(&mosi);
    hal_gpio_define(&sck);
    hal_gpio_update();

    // Enable SPI in master mode
    SPCR |= (1 << SPE) | (1 << MSTR);

    if (spi->interrupts)
    {
        SPCR |= (1 << SPIE);
        sei();
    }

    if (spi->order == HAL_SPI_BIT_ORDER_LSB_FIRST)
    {
        SPCR |= (1 << DORD);
    }

    if (spi->clock_polarity == HAL_SPI_CLOCK_POLARITY_FALLING_RISING)
    {
        SPCR |= (1 << CPOL);
    }

    if (spi->clock_phase == HAL_SPI_CLOCK_PHASE_SETUP_SAMPLE)
    {
        SPCR |= (1 << CPHA);
    }

    switch (spi->prescaller)
    {
        case HAL_SPI_PRESCALLER_2:
            SPCR &= ~((1 << SPR1) | (1 << SPR0));
            SPSR |= (1 << SPI2X);
            break;
        case HAL_SPI_PRESCALLER_8:
            SPCR &= ~(1 << SPR1);
            SPCR |= (1 << SPR0);
            SPSR |= (1 << SPI2X);
            break;
        case HAL_SPI_PRESCALLER_16:
            SPCR &= ~(1 << SPR1);
            SPCR |= (1 << SPR0);
            SPSR &= ~(1 << SPI2X);
            break;
        case HAL_SPI_PRESCALLER_32:
            SPCR |= (1 << SPR1);
            SPCR &= ~(1 << SPR0);
            SPSR |= (1 << SPI2X);
            break;
        case HAL_SPI_PRESCALLER_64:
            SPCR |= (1 << SPR1);
            SPCR &= ~(1 << SPR0);
            SPSR &= ~(1 << SPI2X);
            break;
        case HAL_SPI_PRESCALLER_128:
            SPCR |= (1 << SPR1) | (1 << SPR0);
            SPSR &= ~(1 << SPI2X);
            break;
        case HAL_SPI_PRESCALLER_4:
        default:
            SPCR &= ~((1 << SPR1) | (1 << SPR0));
            SPSR &= ~(1 << SPI2X);
    }
}

uint8_t
hal_spi_master_transmit_receive(uint8_t const chr)
{
    SPDR = chr;
    while (!(SPSR & (1 << SPIF)))
        ;
    return SPDR;
}

void
hal_spi_master_transmit(uint8_t const chr)
{
    SPDR = chr;
}

__attribute__((weak)) void
hal_spi_transfer_complete_isr(uint8_t const chr)
{
}

ISR(SPI_STC_vect)
{
    hal_spi_transfer_complete_isr(SPDR);
}
