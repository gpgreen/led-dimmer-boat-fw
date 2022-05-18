# led-dimmer-boat-fw
Firmware project for the led dimmer for boat hardware.  The firmware
will light a 3 color LED strip using input from a potentiometer to dim
the lighting. The hardware also uses an On-Off-On switch. If the
switch is thrown one way the lighting will be white, if thrown the
other way, the lighting will be red.

The firmware is for a ATtiny13A 8-bit microprocessor and is written in 'c'.

## Building and firmware load

This is a ![CMake](https://cmake.org) project.

### Prerequisites:
 - avr-gcc
 - avr-libc
 - avrdude
 - cmake
 - ninja
 - ![build-tools](https//github.com/gpgreen/avfirmware-build-tools)

### Configure
To configure the firmware for a build run cmake as follows:
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
