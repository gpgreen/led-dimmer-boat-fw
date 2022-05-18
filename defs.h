/*
 * Define registers and pins
 * ATtiny13
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

#define RED_DRIVER_PIN 0
#define RED_DRIVER_REG OCR0A
#define GB_DRIVER_PIN 1
#define GB_DRIVER_REG OCR0B
#define POT_PIN 3
#define RED_SEL_PIN 4

/*-----------------------------------------------------------------------*/

#endif  // DEFS_H_
