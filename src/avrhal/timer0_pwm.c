#include <avr/io.h>
#include <avrhal/gpio.h>
#include <avrhal/timer0.h>
#include <avrhal/timer0_pwm.h>

hal_gpio_t static oc0a = {HAL_GPIO_OC0A, HAL_GPIO_OUTPUT};
hal_gpio_t static oc0b = {HAL_GPIO_OC0B, HAL_GPIO_OUTPUT};

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
init_oc0x_pins_as_output_if_required(hal_timer0_pwm_t const *pwm)
{
    if (pwm->channel_a.mode != HAL_TIMER0_PWM_CHANNEL_DISCONNECTED)
    {
        hal_gpio_define(&oc0a);
    }

    if (pwm->channel_b.mode != HAL_TIMER0_PWM_CHANNEL_DISCONNECTED)
    {
        hal_gpio_define(&oc0b);
    }

    hal_gpio_update();
}

static void
apply_com0nx(hal_timer0_pwm_channel_mode_t const channel_mode,
             uint8_t const                       com0n1_bit,
             uint8_t const                       com0n0_bit)
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
hal_timer0_pwm_init(hal_timer0_pwm_t const *pwm)
{
    uint8_t tccr0a_mask = 0;
    uint8_t tccr0b_mask = 0;
    switch (pwm->mode)
    {
        case HAL_TIMER0_PWM_PHASE_CORRECT:
            tccr0a_mask |= (1 << WGM00);
            tccr0a_mask &= ~(1 << WGM01);
            tccr0b_mask &= ~(1 << WGM02);
            break;
        case HAL_TIMER0_PWM_FAST:
        default:
            tccr0a_mask |= (1 << WGM01) | (1 << WGM00);
            tccr0b_mask &= ~(1 << WGM02);
    }

    TCCR0A = tccr0a_mask;
    TCCR0B = tccr0b_mask;
    OCR0A  = compute_ocrnx(pwm->channel_a.duty_cycle);
    OCR0B  = compute_ocrnx(pwm->channel_b.duty_cycle);

    init_oc0x_pins_as_output_if_required(pwm);
}

void
hal_timer0_pwm_run(hal_timer0_pwm_t const *pwm)
{
    apply_com0nx(pwm->channel_a.mode, COM0A1, COM0A0);
    apply_com0nx(pwm->channel_b.mode, COM0B1, COM0B0);
    hal_timer0_run(pwm->prescaller);
}

void
hal_timer0_pwm_stop(hal_timer0_pwm_t const *pwm)
{
    hal_timer0_stop();
    apply_com0nx(HAL_TIMER0_PWM_CHANNEL_DISCONNECTED, COM0A1, COM0A0);
    apply_com0nx(HAL_TIMER0_PWM_CHANNEL_DISCONNECTED, COM0B1, COM0B0);
}