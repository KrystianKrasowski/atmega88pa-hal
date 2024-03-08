#include "spi.h"
#include "unity_config.h"
#include <unity/unity.h>

// SPI Control register
uint8_t SPCR = 0;

// bit indexes
uint8_t SPIE = 7;
uint8_t SPE  = 6;
uint8_t DORD = 5;
uint8_t MSTR = 4;
uint8_t CPOL = 3;
uint8_t CPHA = 2;
uint8_t SPR1 = 1;
uint8_t SPR0 = 0;

// SPI Status register
uint8_t SPSR = 0;

// bit indexes
uint8_t SPIF  = 7;
uint8_t WCOL  = 6;
uint8_t SPI2X = 0;

// SPI Data regiser
uint8_t SPDR = 0;

// SPI GPIO Register
uint8_t SS_DDR  = 0;
uint8_t SS_PORT = 0;
uint8_t SS_BIT  = 2;

uint8_t MOSI_DDR = 0;
uint8_t MOSI_BIT = 3;

uint8_t SCK_DDR = 0;
uint8_t SCK_BIT = 5;

// Interrupts
void
sei(void)
{
}

// Test data
hal_spi_def_t spi_definition = {};

#define SPIE_BIT  (1 << SPIE)
#define SPE_BIT   (1 << SPE)
#define DORD_BIT  (1 << DORD)
#define MSTR_BIT  (1 << MSTR)
#define CPOL_BIT  (1 << CPOL)
#define CPHA_BIT  (1 << CPHA)
#define SPR1_BIT  (1 << SPR1)
#define SPR0_BIT  (1 << SPR0)
#define SPI2X_BIT (1 << SPI2X)

void
should_pull_up_ss_on_master_mode(void)
{
    // when
    hal_spi_master_init(&spi_definition);

    // then
    TEST_ASSERT_BIT_HIGH(SS_BIT, SS_PORT);
    TEST_ASSERT_BIT_HIGH(MOSI_BIT, MOSI_DDR);
    TEST_ASSERT_BIT_HIGH(SCK_BIT, SCK_DDR);
}

void
should_initialize_master_data_order(hal_spi_bit_order_t dord,
                                    uint8_t             expected_spcr)
{
    // given
    spi_definition.order = dord;

    // when
    hal_spi_master_init(&spi_definition);

    // then
    TEST_ASSERT_BITS(0xff, expected_spcr, SPCR);
}

void
should_initialize_master_clock_polarity(hal_spi_clock_polarity_t cpol,
                                        uint8_t                  expected_spcr)
{
    // given
    spi_definition.cpol = cpol;

    // when
    hal_spi_master_init(&spi_definition);

    // then
    TEST_ASSERT_BITS(0xff, expected_spcr, SPCR);
}

void
should_initialize_master_clock_phase(hal_spi_clock_phase_t cpha,
                                     uint8_t               expected_spcr)
{
    // given
    spi_definition.cpha = cpha;

    // when
    hal_spi_master_init(&spi_definition);

    // then
    TEST_ASSERT_BITS(0xff, expected_spcr, SPCR);
}

void
should_initialize_master_clock(hal_spi_prescaller_t presc,
                               uint8_t              expected_spcr,
                               uint8_t              expected_spsr)
{
    // given
    spi_definition.presc = presc;

    // when
    hal_spi_master_init(&spi_definition);

    // then
    TEST_ASSERT_BITS(0xff, expected_spcr, SPCR);
    TEST_ASSERT_BITS(0xff, expected_spsr, SPSR);
}

void
should_initialize_spi_interrupts()
{
    // given
    spi_definition.interrupts = 1;

    // when
    hal_spi_master_init(&spi_definition);

    // then
    TEST_ASSERT_BITS(0xff, SPIE_BIT | SPE_BIT | MSTR_BIT, SPCR);
}

void
should_transmit_char(void)
{
    // when
    hal_spi_master_transmit(0xff);

    // then
    TEST_ASSERT_EQUAL_HEX8(0xff, SPDR);
}

void
setUp()
{
    SPCR                 = 0;
    SPSR                 = 0;
    SPDR                 = 0;
    spi_definition.order = 0;
    spi_definition.cpol  = 0;
    spi_definition.cpha  = 0;
    spi_definition.presc = 0;
}

void
tearDown()
{
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_TEST(should_pull_up_ss_on_master_mode);

    RUN_TEST(should_initialize_master_data_order,
             HAL_SPI_BIT_ORDER_MSB_FIRST,
             SPE_BIT | MSTR_BIT);

    RUN_TEST(should_initialize_master_data_order,
             HAL_SPI_BIT_ORDER_LSB_FIRST,
             SPE_BIT | MSTR_BIT | DORD_BIT);

    RUN_TEST(should_initialize_master_clock_polarity,
             HAL_SPI_CLOCK_POLARITY_RISING_FALLING,
             SPE_BIT | MSTR_BIT);

    RUN_TEST(should_initialize_master_clock_polarity,
             HAL_SPI_CLOCK_POLARITY_FALLING_RISING,
             SPE_BIT | MSTR_BIT | CPOL_BIT);

    RUN_TEST(should_initialize_master_clock_phase,
             HAL_SPI_CLOCK_PHASE_SAMPLE_SETUP,
             SPE_BIT | MSTR_BIT);

    RUN_TEST(should_initialize_master_clock_phase,
             HAL_SPI_CLOCK_PHASE_SETUP_SAMPLE,
             SPE_BIT | MSTR_BIT | CPHA_BIT);

    RUN_TEST(should_initialize_master_clock,
             HAL_SPI_PRESCALLER_2,
             SPE_BIT | MSTR_BIT,
             SPI2X_BIT);

    RUN_TEST(should_initialize_master_clock,
             HAL_SPI_PRESCALLER_4,
             SPE_BIT | MSTR_BIT,
             0);

    RUN_TEST(should_initialize_master_clock,
             HAL_SPI_PRESCALLER_8,
             SPE_BIT | MSTR_BIT | SPR0_BIT,
             SPI2X_BIT);

    RUN_TEST(should_initialize_master_clock,
             HAL_SPI_PRESCALLER_16,
             SPE_BIT | MSTR_BIT | SPR0_BIT,
             0);

    RUN_TEST(should_initialize_master_clock,
             HAL_SPI_PRESCALLER_32,
             SPE_BIT | MSTR_BIT | SPR1_BIT,
             SPI2X_BIT);

    RUN_TEST(should_initialize_master_clock,
             HAL_SPI_PRESCALLER_64,
             SPE_BIT | MSTR_BIT | SPR1_BIT,
             0);

    RUN_TEST(should_initialize_master_clock,
             HAL_SPI_PRESCALLER_128,
             SPE_BIT | MSTR_BIT | SPR1_BIT | SPR0_BIT,
             0);

    RUN_TEST(should_initialize_spi_interrupts);

    RUN_TEST(should_transmit_char);

    return UNITY_END();
}
