/*
 * Define registers and pins
 * ATtiny13 or ATtiny26
 * led-dimmer-boat board
 */
#ifndef DEFS_H_
#define DEFS_H_

/*-----------------------------------------------------------------------*/

/*
 * Hardware and software revisions
 */
#define HARDWARE_REVISION 1
#define SOFTWARE_REVISION 1

/*-----------------------------------------------------------------------*/

/* specific pins */

#ifdef USE_PROTO

#define RED_DRIVER_PIN 1
#define RED_DRIVER_REG OCR1A
#define GB_DRIVER_PIN 3
#define GB_DRIVER_REG OCR1B

#define _ADCSR ADCSR

#else

#define RED_DRIVER_PIN 0
#define RED_DRIVER_REG OCR0A
#define GB_DRIVER_PIN 1
#define GB_DRIVER_REG OCR0B

#define _ADCSR ADCSRA

#endif

#define RED_SEL_PIN 4

/*-----------------------------------------------------------------------*/

#endif  // DEFS_H_
