#include "avrhal/timer0_pwm.h"
#include <avr/io.h>

static uint8_t
compute_ocrnx(uint8_t duty_cycle)
{
    if (duty_cycle > 100)
    {
        duty_cycle = 100;
    }

    return (255 * duty_cycle) / 100;
}

static void
apply_com0nx(hal_timer0_pwm_channel_mode_t channel_mode,
             uint8_t                       com0n1_bit,
             uint8_t                       com0n0_bit)
{
    switch (channel_mode)
    {
        case HAL_TIMER0_PWM_CHANNEL_NON_INVERTING:
            TCCR0A |= (1 << com0n1_bit);
            TCCR0A &= ~(1 << com0n0_bit);
            break;
        case HAL_TIMER0_PWM_CHANNEL_INVERTING:
            TCCR0A |= (1 << com0n1_bit) | (1 << com0n0_bit);
            break;
        // According to atmega88pa datasheet, channel B has no compare match
        // mode, thus this HAL use case falls back to disconnected mode on
        // channel B
        case HAL_TIMER0_PWM_CHANNEL_TOGGLE_ON_COMPARE:
            if (com0n1_bit == COM0B1 && com0n0_bit == COM0B0)
            {
                TCCR0A &= ~((1 << com0n1_bit) | (1 << com0n0_bit));
            }
            else
            {
                TCCR0A &= ~(1 << com0n1_bit);
                TCCR0A |= (1 << com0n0_bit);
            }
            break;
        case HAL_TIMER0_PWM_CHANNEL_DISCONNECTED:
        default:
            TCCR0A &= ~((1 << com0n1_bit) | (1 << com0n0_bit));
            break;
    }
}

void
hal_timer0_pwm_init(const hal_timer0_pwm_t *pwm)
{
    switch (pwm->mode)
    {
        case HAL_TIMER0_PWM_PHASE_CORRECT:
            TCCR0A |= (1 << WGM00);
            TCCR0A &= ~(1 << WGM01);
            TCCR0B &= ~(1 << WGM02);
            break;
        case HAL_TIMER0_PWM_FAST:
        default:
            TCCR0A |= (1 << WGM01) | (1 << WGM00);
            TCCR0B &= ~(1 << WGM02);
    }

    apply_com0nx(pwm->channel_a.mode, COM0A1, COM0A0);
    apply_com0nx(pwm->channel_b.mode, COM0B1, COM0B0);

    OCR0A = compute_ocrnx(pwm->channel_a.duty_cycle);
    OCR0B = compute_ocrnx(pwm->channel_b.duty_cycle);
}