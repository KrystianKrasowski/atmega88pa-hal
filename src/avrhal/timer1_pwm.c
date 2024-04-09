#include "avrhal/timer1_pwm.h"
#include "avrhal/timer1.h"
#include <avr/io.h>

hal_gpio_t static oc1a = {HAL_GPIO_OC1A, HAL_GPIO_OUTPUT};
hal_gpio_t static oc1b = {HAL_GPIO_OC1B, HAL_GPIO_OUTPUT};

static uint8_t
compute_ocrnx_8bit(uint8_t duty_cycle)
{
    if (duty_cycle > 100)
    {
        duty_cycle = 100;
    }

    return (255 * duty_cycle) / 100;
}

static void
init_oc1x_pins_as_output_if_required(hal_timer1_pwm_t const *pwm)
{
    if (pwm->channel_a.mode != HAL_TIMER1_PWM_CHANNEL_DISCONNECTED)
    {
        hal_gpio_define(&oc1a);
    }

    if (pwm->channel_b.mode != HAL_TIMER1_PWM_CHANNEL_DISCONNECTED)
    {
        hal_gpio_define(&oc1b);
    }

    hal_gpio_update();
}

static void
apply_com1nx(hal_timer1_pwm_channel_mode_t const channel_mode,
             uint8_t const                       com1n1_bit,
             uint8_t const                       com1n0_bit)
{
    switch (channel_mode)
    {
        case HAL_TIMER1_PWM_CHANNEL_NON_INVERTING:
            TCCR1A |= (1 << com1n1_bit);
            TCCR1A &= ~(1 << com1n0_bit);
            break;
        case HAL_TIMER1_PWM_CHANNEL_INVERTING:
            TCCR1A |= (1 << com1n1_bit) | (1 << com1n0_bit);
            break;
        // According to atmega88pa datasheet, channel B has no compare match
        // mode, thus this HAL use case falls back to disconnected mode on
        // channel B
        case HAL_TIMER1_PWM_CHANNEL_TOGGLE_ON_COMPARE:
            if (com1n1_bit == COM1B1 && com1n0_bit == COM1B0)
            {
                TCCR1A &= ~((1 << com1n1_bit) | (1 << com1n0_bit));
            }
            else
            {
                TCCR1A &= ~(1 << com1n1_bit);
                TCCR1A |= (1 << com1n0_bit);
            }
            break;
        case HAL_TIMER1_PWM_CHANNEL_DISCONNECTED:
        default:
            TCCR1A &= ~((1 << com1n1_bit) | (1 << com1n0_bit));
            break;
    }
}

void
hal_timer1_pwm_init(hal_timer1_pwm_t const *pwm)
{
    uint8_t tccr1a_mask = 0;
    uint8_t tccr1b_mask = 0;
    
    switch (pwm->mode)
    {
        case HAL_TIMER1_PWM_PHASE_CORRECT_8BIT:
            tccr1b_mask &= ~(1 << WGM13);
            tccr1b_mask &= ~(1 << WGM12);
            tccr1a_mask &= ~(1 << WGM11);
            tccr1a_mask |= (1 << WGM10);
            OCR1B = compute_ocrnx_8bit(pwm->channel_b.duty_cycle);
            OCR1A = compute_ocrnx_8bit(pwm->channel_a.duty_cycle);
            break;
        case HAL_TIMER1_PWM_FAST_8BIT:
        default:
            tccr1b_mask &= ~(1 << WGM13);
            tccr1b_mask |= (1 << WGM12);
            tccr1a_mask &= ~(1 << WGM11);
            tccr1a_mask |= (1 << WGM10);
            OCR1B = compute_ocrnx_8bit(pwm->channel_b.duty_cycle);
            OCR1A = compute_ocrnx_8bit(pwm->channel_a.duty_cycle);
            break;
    }

    TCCR1A = tccr1a_mask;
    TCCR1B = tccr1b_mask;
    
    init_oc1x_pins_as_output_if_required(pwm);
}

void
hal_timer1_pwm_run(hal_timer1_pwm_t const *pwm)
{
    apply_com1nx(pwm->channel_a.mode, COM1A1, COM1A0);
    apply_com1nx(pwm->channel_b.mode, COM1B1, COM1B0);
    hal_timer1_run(pwm->prescaller);
}

void
hal_timer1_pwm_stop(hal_timer1_pwm_t const *pwm)
{
    hal_timer1_stop();
    apply_com1nx(HAL_TIMER1_PWM_CHANNEL_DISCONNECTED, COM1A1, COM1A0);
    apply_com1nx(HAL_TIMER1_PWM_CHANNEL_DISCONNECTED, COM1B1, COM1B0);
}