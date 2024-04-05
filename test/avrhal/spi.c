#include "avrhal/spi.h"
#include "avr/io.h"
#include "avr/stub.h"
#include "helpers.h"
#include "unity_config.h"
#include <stdbool.h>
#include <unity.h>

hal_spi_t spi = {};

void
setUp(void)
{
    SPCR = 0;
    SPSR = 0;
    SPDR = 0;
}

void
tearDown(void)
{
}

void
should_init_as_master(void)
{
    // when
    hal_spi_master_init(&spi);

    // then
    TEST_ASSERT_BIT_HIGH(MSTR, SPCR);
    TEST_ASSERT_BIT_HIGH(MOSI_BIT, MOSI_DDR);
    TEST_ASSERT_BIT_HIGH(SCK_BIT, SCK_DDR);
}

void
should_pull_up_ss_on_master_mode(void)
{
    // when
    hal_spi_master_init(&spi);

    // then
    TEST_ASSERT_BIT_HIGH(SS_BIT, SS_PORT);
}

void
should_init_sending_lsb_first(void)
{
    //  given
    spi.order = HAL_SPI_BIT_ORDER_LSB_FIRST;

    // when
    hal_spi_master_init(&spi);

    // then
    TEST_ASSERT_BIT_HIGH(DORD, SPCR);
}

void
should_init_sending_msb_first(void)
{
    //  given
    spi.order = HAL_SPI_BIT_ORDER_MSB_FIRST;

    // when
    hal_spi_master_init(&spi);

    // then
    TEST_ASSERT_BIT_LOW(DORD, SPCR);
}

void
should_init_clock_polarity_rising_falling(void)
{
    // given
    spi.clock_polarity = HAL_SPI_CLOCK_POLARITY_RISING_FALLING;

    // when
    hal_spi_master_init(&spi);

    // then
    TEST_ASSERT_BIT_LOW(CPOL, SPCR);
}

void
should_init_clock_polarity_falling_rising(void)
{
    // given
    spi.clock_polarity = HAL_SPI_CLOCK_POLARITY_FALLING_RISING;

    // when
    hal_spi_master_init(&spi);

    // then
    TEST_ASSERT_BIT_HIGH(CPOL, SPCR);
}

void
should_init_clock_phase_sample_setup(void)
{
    // given
    spi.clock_phase = HAL_SPI_CLOCK_PHASE_SAMPLE_SETUP;

    // when
    hal_spi_master_init(&spi);

    // then
    TEST_ASSERT_BIT_LOW(CPHA, SPCR);
}

void
should_init_clock_phase_setup_sample(void)
{
    // given
    spi.clock_phase = HAL_SPI_CLOCK_PHASE_SETUP_SAMPLE;

    // when
    hal_spi_master_init(&spi);

    // then
    TEST_ASSERT_BIT_HIGH(CPHA, SPCR);
}

void
should_init_clock(hal_spi_prescaller_t prescaller,
                  uint8_t              spi2x,
                  uint8_t              spr1,
                  uint8_t              spr0)
{
    // given
    spi.prescaller = prescaller;

    // when
    hal_spi_master_init(&spi);

    // then
    TEST_ASSERT_BIT_STATE_MESSAGE(SPI2X, spi2x, SPSR, "Unexpected SPI2X");
    TEST_ASSERT_BIT_STATE_MESSAGE(SPR1, spr1, SPCR, "Unexpected SPR1");
    TEST_ASSERT_BIT_STATE_MESSAGE(SPR0, spr0, SPCR, "Unexpected SPR0");
}

void
should_init_interrupts(void)
{
    // given
    spi.interrupts = true;

    // when
    hal_spi_master_init(&spi);

    // then
    TEST_ASSERT_BIT_HIGH(SPIE, SPCR);
    TEST_ASSERT_TRUE(is_global_interrupts_enable());
}

void
should_transmit_and_receive(void)
{
    // given
    SPSR |= (1 << SPIF);

    // when
    uint8_t response = hal_spi_master_transmit_receive(0xab);

    // then
    TEST_ASSERT_EQUAL(0xab, SPDR);
    TEST_ASSERT_EQUAL(0xab, response);
}

void
should_transmit(void)
{
    // when
    hal_spi_master_transmit(0xab);

    // then
    TEST_ASSERT_EQUAL(0xab, SPDR);
}

int
main(void)
{
    UNITY_BEGIN();

    RUN_TEST(should_init_as_master);
    RUN_TEST(should_pull_up_ss_on_master_mode);
    RUN_TEST(should_init_sending_lsb_first);
    RUN_TEST(should_init_sending_msb_first);
    RUN_TEST(should_init_clock_polarity_rising_falling);
    RUN_TEST(should_init_clock_polarity_falling_rising);
    RUN_TEST(should_init_clock_phase_sample_setup);
    RUN_TEST(should_init_clock_phase_setup_sample);

    RUN_PARAM_TEST(should_init_clock,
                   HAL_SPI_PRESCALLER_2,
                   BIT(SPI2X),
                   ~BIT(SPR1),
                   ~BIT(SPR0));

    RUN_PARAM_TEST(should_init_clock,
                   HAL_SPI_PRESCALLER_4,
                   ~BIT(SPI2X),
                   ~BIT(SPR1),
                   ~BIT(SPR0));

    RUN_PARAM_TEST(should_init_clock,
                   HAL_SPI_PRESCALLER_8,
                   BIT(SPI2X),
                   ~BIT(SPR1),
                   BIT(SPR0));

    RUN_PARAM_TEST(should_init_clock,
                   HAL_SPI_PRESCALLER_16,
                   ~BIT(SPI2X),
                   ~BIT(SPR1),
                   BIT(SPR0));

    RUN_PARAM_TEST(should_init_clock,
                   HAL_SPI_PRESCALLER_32,
                   BIT(SPI2X),
                   BIT(SPR1),
                   ~BIT(SPR0));

    RUN_PARAM_TEST(should_init_clock,
                   HAL_SPI_PRESCALLER_64,
                   ~BIT(SPI2X),
                   BIT(SPR1),
                   ~BIT(SPR0));

    RUN_PARAM_TEST(should_init_clock,
                   HAL_SPI_PRESCALLER_128,
                   ~BIT(SPI2X),
                   BIT(SPR1),
                   BIT(SPR0));

    RUN_TEST(should_init_interrupts);
    RUN_TEST(should_transmit_and_receive);
    RUN_TEST(should_transmit);

    return UNITY_END();
}