#include "avrhal/spi.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void
hal_spi_master_init(const hal_spi_t *spi)
{
    // This is necessary to maintain uC in SPI master mode
    SS_PORT |= (1 << SS_BIT);
    MOSI_DDR |= (1 << MOSI_BIT);
    SCK_DDR |= (1 << SCK_BIT);

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
hal_spi_master_transmit_receive(const uint8_t chr)
{
    SPDR = chr;
    while (!(SPSR & (1 << SPIF)))
        ;
    return SPDR;
}

void
hal_spi_master_transmit(const uint8_t chr)
{
    SPDR = chr;
}

__attribute__((weak)) void
hal_spi_transfer_complete_isr(const uint8_t chr)
{
}

ISR(SPI_STC_vect)
{
    hal_spi_transfer_complete_isr(SPDR);
}
