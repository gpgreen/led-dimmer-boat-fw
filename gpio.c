#include <inttypes.h>
#include <avr/io.h>

#include "gpio.h"

void gpio_setup(void)
{
    // setup the led driver pins, level lo
    DDRB |= _BV(RED_DRIVER_PIN) & _BV(GB_DRIVER_PIN);
    PORTB &= ~(_BV(RED_DRIVER_PIN) & _BV(GB_DRIVER_PIN));

#ifdef USE_PROTO
    // set pullups on unused pins
    PORTA |= _BV(0) | _BV(1) | _BV(2) | _BV(3) | _BV(5) | _BV(6) | _BV(7);
    PORTB |= _BV(0) | _BV(2) | _BV(5) | _BV(6);
#else
    // setup pin 2 as input with pullup as it is floating
    PORTB |= _BV(2);
#endif
}
