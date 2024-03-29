#include "avr/io.h"
#include "avrhal/spi.h"
#include "helpers.h"
#include "unity_config.h"
#include <stdbool.h>
#include <unity.h>

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
    RUN_TEST(should_transmit_and_receive);
    RUN_TEST(should_transmit);
    return UNITY_END();
}