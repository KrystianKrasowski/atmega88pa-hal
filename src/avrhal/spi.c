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

    uint8_t spcr_mask = 0;
    uint8_t spsr_mask = 0;

    // Enable SPI in master mode
    spcr_mask |= (1 << SPE) | (1 << MSTR);

    if (spi->interrupts)
    {
        spcr_mask |= (1 << SPIE);
        sei();
    }

    if (spi->order == HAL_SPI_BIT_ORDER_LSB_FIRST)
    {
        spcr_mask |= (1 << DORD);
    }

    if (spi->clock_polarity == HAL_SPI_CLOCK_POLARITY_FALLING_RISING)
    {
        spcr_mask |= (1 << CPOL);
    }

    if (spi->clock_phase == HAL_SPI_CLOCK_PHASE_SETUP_SAMPLE)
    {
        spcr_mask |= (1 << CPHA);
    }

    switch (spi->prescaller)
    {
        case HAL_SPI_PRESCALLER_2:
            spcr_mask &= ~((1 << SPR1) | (1 << SPR0));
            spsr_mask |= (1 << SPI2X);
            break;
        case HAL_SPI_PRESCALLER_8:
            spcr_mask &= ~(1 << SPR1);
            spcr_mask |= (1 << SPR0);
            spsr_mask |= (1 << SPI2X);
            break;
        case HAL_SPI_PRESCALLER_16:
            spcr_mask &= ~(1 << SPR1);
            spcr_mask |= (1 << SPR0);
            spsr_mask &= ~(1 << SPI2X);
            break;
        case HAL_SPI_PRESCALLER_32:
            spcr_mask |= (1 << SPR1);
            spcr_mask &= ~(1 << SPR0);
            spsr_mask |= (1 << SPI2X);
            break;
        case HAL_SPI_PRESCALLER_64:
            spcr_mask |= (1 << SPR1);
            spcr_mask &= ~(1 << SPR0);
            spsr_mask &= ~(1 << SPI2X);
            break;
        case HAL_SPI_PRESCALLER_128:
            spcr_mask |= (1 << SPR1) | (1 << SPR0);
            spsr_mask &= ~(1 << SPI2X);
            break;
        case HAL_SPI_PRESCALLER_4:
        default:
            spcr_mask &= ~((1 << SPR1) | (1 << SPR0));
            spsr_mask &= ~(1 << SPI2X);
    }

    SPCR = spcr_mask;
    SPSR = spsr_mask;
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
