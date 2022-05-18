#include <inttypes.h>
#include <avr/io.h>

#include "gpio.h"

void gpio_setup(void)
{
  // setup the led driver pins, level lo
  // PB0 - red driver
  // PB1 - blue/green driver
  DDRB |= _BV(RED_DRIVER_PIN) & _BV(BG_DRIVER_PIN);
  PORTB &= ~(_BV(RED_DRIVER_PIN) & _BV(BG_DRIVER_PIN));

  // setup the potentiometer input, PB3
  DDRB &= ~_BV(POT_PIN);

  // setup the red select input, PB4
  DDRB &= ~_BV(RED_SEL_PIN);

  // setup pin 2 as input with pullup as it is floating
  DDRB &= ~_BV(2);
  PORTB |= _BV(2);
}
