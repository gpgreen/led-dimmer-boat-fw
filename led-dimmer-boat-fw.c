/*
 * Fuse bits for ATtiny13
 * Full swing oscillator, start up 14ck + 64ms, internal rc occ
 * clock prescaler divide by 8
 * watchdog timer always on
 * serial programming downloading enabled
 * self programming enabled
 * brown-out at 4.3V
 * Low=0x4a Hi=0xe9
 * avrdude settings:
 * -U lfuse:w:0x4a:m -U hfuse:w:0xe9:m
 * from http://www.engbedded.com/fusecalc/
 */

#include "defs.h"
#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include <math.h>
#include "globals.h"

/*-----------------------------------------------------------------------*/

void
ioinit(void)
{
  gpio_setup();

  // starting PWM drivers at level 0
  RED_DRIVER_REG = 0;
  BG_DRIVER_REG = 0;
  // setup timer for Fast PWM
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
  TCCR0B = _BV(CS00);

  // setup adc
  // voltage reference Vcc
  // select ADC3 as input (PB3)
  ADMUX = _BV(MUX1) | _BV(MUX0);
  // enable adc, start converting, input clock to clk/128
  ADCSRA |= _BV(ADEN) | _BV(ADSC) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
  // disable digital input buffer for the analog input pin
  DIDR0 |= _BV(ADC3D);
  // loop until the conversion is complete, then start again to discard first value
  while ((ADCSRA & _BV(ADSC)) == _BV(ADSC));
  // start conversion again
  ADCSRA |= _BV(ADSC);
  _delay_ms(50);
}

/*-----------------------------------------------------------------------*/

int
main(void)
{
  // first set the clock prescaler change enable
  CLKPR = _BV(CLKPCE);
  // now set the clock prescaler to clk/1
  CLKPR = 0;

  ioinit();

  while(1)
    {
      // get the adc value
      while ((ADCSRA & _BV(ADSC)) == _BV(ADSC));
      uint16_t val = ADCL;
      val += (ADCH << 8);
      val *= 255;
      val /= 1023;
      // start the adc again
      ADCSRA |= _BV(ADSC);

      // if the RED_SEL_PIN is high, red color is NOT selected
      int red_selected = ((PINB & _BV(RED_SEL_PIN)) == _BV(RED_SEL_PIN)) ? 0 : 1;

      // set the duty cycle
      uint8_t duty_cycle = (uint8_t)val;
      if (red_selected) {
        RED_DRIVER_REG = duty_cycle;
        BG_DRIVER_REG = 0;
      } else {
        RED_DRIVER_REG = duty_cycle;
        BG_DRIVER_REG = duty_cycle;
      }

      // delay
      _delay_ms(10);
    }
  return 0;
}

/*-----------------------------------------------------------------------*/
