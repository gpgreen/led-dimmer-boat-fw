/*
 * led-dimmer-boat-fw.c
 * main program for boat led dimmer
 */

#include "defs.h"
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "gpio.h"
#include <math.h>
#include "globals.h"

/*-----------------------------------------------------------------------*/

/* static variables */
uint8_t output_compare_red = 0;
uint8_t output_compare_greenblue = 0;
uint8_t mcusr_mirror __attribute__ ((section (".noinit")));

/*-----------------------------------------------------------------------*/
// disable the watchdog during startup
void get_mcusr(void) \
    __attribute__((naked))                      \
    __attribute__((section(".init3")));
void get_mcusr(void)
{
    mcusr_mirror = MCUSR;
    MCUSR = 0;
    wdt_disable();
}

/*-----------------------------------------------------------------------*/

void
ioinit(void)
{
    gpio_setup();

    // starting PWM drivers at level 0
    RED_DRIVER_REG = 0;
    GB_DRIVER_REG = 0;
#ifdef USE_PROTO
    // setup timer for Fast PWM
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(PWM1A) | _BV(PWM1B);
    TCCR1B = _BV(CS10);
    OCR1C = 255;
#else
    // setup timer for Phase correct PWM
    TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    // clock divided by 8
    TCCR0B = _BV(CS01);
#endif

    // setup adc
    // voltage reference Vcc
    // select ADC3 as input
    ADMUX = _BV(MUX1) | _BV(MUX0);
#ifndef USE_PROTO
    // disable digital input buffer for the analog input pin
    DIDR0 |= _BV(ADC3D);
#endif
    // enable adc, start converting, input clock to clk/128
    _ADCSR |= _BV(ADEN) | _BV(ADSC) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    // loop until the conversion is complete, then start again to discard first value
    while ((_ADCSR & _BV(ADSC)) == _BV(ADSC));
    // start conversion again
    _ADCSR |= _BV(ADSC);

    // watchdog setup
    WDTCR |= _BV(WDCE) | _BV(WDE); // start timed sequence
#ifdef USE_PROTO
    // wdt prescalar change (.27s)
    WDTCR = _BV(WDE) | _BV(WDP2);
#else
    // wdt prescalar change (.25s)
    WDTCR = _BV(WDE) | _BV(WDP2) | _BV(WDP0);
#endif

    // delay for a while
    _delay_ms(50);
}

/*-----------------------------------------------------------------------*/

int
main(void)
{
#ifndef USE_PROTO
    // start timed sequence
    CLKPR = _BV(CLKPCE);
    // now set the clock prescaler to clk/1
    CLKPR = 0;
#endif

    ioinit();
    sei();

    while(1)
    {
        // reset the watchdog
        wdt_reset();

        // get the adc value
        while ((_ADCSR & _BV(ADSC)) == _BV(ADSC));
        uint16_t val = ADCL;
        val += (ADCH << 8);
        // divide by 4
        val >>= 2;
        if (val > 255)
            val = 255;
        if (val < 10)
            val = 10;
        // start the adc again
        _ADCSR |= _BV(ADSC);

        // if the RED_SEL_PIN is high, red color is NOT selected
        int red_selected = ((PINB & _BV(RED_SEL_PIN)) == _BV(RED_SEL_PIN)) ? 0 : 1;

        // set the duty cycle
        uint8_t duty_cycle = (uint8_t)val;
        if (red_selected) {
            output_compare_red = duty_cycle;
            output_compare_greenblue = 0;
        } else {
            output_compare_red = duty_cycle;
            output_compare_greenblue = duty_cycle;
        }
#ifdef USE_PROTO
        // in attiny26, the OCR registers are updated on OCR1C overflow, so interrupt not required
        RED_DRIVER_REG = output_compare_red;
        GB_DRIVER_REG = output_compare_greenblue;
#else
        // set the overflow interrupt so OCR's can be changed
        TIMSK0 |= _BV(TOIE0);
#endif

        // delay
        _delay_ms(10);
    }
    return 0;
}

/*-----------------------------------------------------------------------*/
#ifndef USE_PROTO

ISR(TIM0_OVF_vect)
{
    RED_DRIVER_REG = output_compare_red;
    GB_DRIVER_REG = output_compare_greenblue;
    // disable the interrupt
    TIMSK0 &= ~_BV(TOIE0);
}

#endif
/*-----------------------------------------------------------------------*/
