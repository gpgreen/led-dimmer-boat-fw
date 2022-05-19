# led-dimmer-boat-fw
Firmware project for the led dimmer for boat hardware.  The firmware
will light a 3 color LED strip using input from a potentiometer to dim
the lighting. The hardware also uses an On-Off-On switch. If the
switch is thrown one way the lighting will be white, if thrown the
other way, the lighting will be red.

The firmware is for a ATtiny13A 8-bit microprocessor and is written in 'c'.

## ATtiny13 pinout
PCB
```
                 ATtiny13A
             +--------------------+
             |                    |
       RESET-|1  PB5             8|-VCC
         POT-|2  PB3        PB2  7|-NC
 RED_SEL_PIN-|3  PB4        PB1  6|-GB_DRIVER
         GND-|4             PB0  5|-RED_DRIVER
             |                    |
             +--------------------+
```

## ATtiny26 pinout
Prototype
```
                 ATtiny26
             +--------------------+
             |                    |
          NC-|1  PB0        PA0 20|-NC
  RED_DRIVER-|2  PB1        PA1 19|-NC
          NC-|3  PB2        PA2 18|-NC
   GB_DRIVER-|4  PB3        PA3 17|-NC
         VCC-|5                 16|-GND
         GND-|6                 15|-AVCC
 RED_SEL_PIN-|7  PB4        PA4 14|-POT
          NC-|8  PB5        PA5 13|-NC
          NC-|9  PB6        PA6 12|-NC
       RESET-|10 PB7        PA7 11|-NC
             |                    |
             +--------------------+
```

## Building and firmware load

This is a ![CMake](https://cmake.org) project.  There is one option
to the build ```PROTO``` for the prototype hardware with attiny26.

### Prerequisites:
 - avr-gcc
 - avr-libc
 - avrdude
 - cmake
 - ninja
 - ![build-tools](https//github.com/gpgreen/avfirmware-build-tools)

### Configure
To configure the firmware for a PROTO build run cmake as follows:
```
cmake -G ninja -DPROTO=ON -DCMAKE_TOOLCHAIN_FILE=<build-tools>/cmake-avr/generic-gcc-avr.cmake
```

To configure the firmware for a pcb build run cmake as follows:
```
cmake -G ninja -DCMAKE_TOOLCHAIN_FILE=<build-tools>/cmake-avr/generic-gcc-avr.cmake
```

To see all targets:
```
ninja help
```

### Build
```
ninja
```

### Install firmware
```
ninja upload-led-dimmer-boat-fw
```

## Hardware project
The kicad project for the [hardware](https://github.com/gpgreen/led-dimmer-boat)
