# BitLoom LED blink

This repository contains a small hack that blinks a LED using the BitLoom
framework. The program is implemented in C and targets different small embedded
microcontrollers (MCUs); at the moment AVR (ATMega328P) and ARM Cortex-M3
([Bluepill](https://stm32-base.org/boards/STM32F103C8T6-Blue-Pill.html)).

## LED blink application

The LED blink (ledblink) hack is a trivial program that flashes a LED on and
off at a regular interval (240 ms). The program has one task (blink_task) that
turns on and off the LED using the pin_digital_io interface. A second task
handles communication over UART that can be used to control the LED blinking.
The implementation utilizes the HAL declared by BitLoom core.

## Cross compilation (Linux)

Cross compilation toolchains are required to build the firmware for the MCUs.
The steps below assume that the build is done on a Linux machine. It should
not be hard to build on Windows or Mac, but that has not been tested.

## AVR port

The port for the AVR uses the timer interface, the IO interface and the UART
interface. The implementation is kept in the submodule `bitloom-avr`.
The port configuration is a custom implementation for this specific hack - 
see `avr_config`.

### Build for AVR

To build the program for AVR, follow the steps below.  It is assumed that an AVR
cross compilation toolchain is installed on the computer and available on the
path. The type of programmer to flash the board can be configured in the
avr-gcc-toolchain.cmake file (USBTinyISP or AVRISP).

 1. git clone https://github.com/bluezephyr/bitloom-ledblink.git
 1. cd bitloom-ledblink
 1. git submodule update --init
 1. mkdir build
 1. cd build
 1. cmake -DCMAKE_TOOLCHAIN_FILE=../bitloom-avr/avr-gcc-toolchain.cmake -DCONFIG=avr_config ..
 1. make
 1. make flash

The program will then be flashed to the MCU and the LED connected to PIN PB1
will start to blink.

## ARM Cortex-M port (Bluepill)

The HAL for the ARM Cortex-M is available in the `bluepill-cmsis` submodule.
The port uses the timer interface and the IO interface. Support for UART is
not implemented yet. The port configuration is a custom implementation stored
in the `bluepill_config` folder.

### Build for ARM

Follow the steps below to build for ARM. It is assumed that the cross 
compilation toolchain is installed in the `/opt/gcc-arm` folder. For 
instructions how to flash to target, see the `bluepill-cmsis` submodule README.

1. git clone https://github.com/bluezephyr/bitloom-ledblink.git
1. cd bitloom-ledblink
1. git submodule update --init
1. mkdir build
1. cd build
1. cmake -DCMAKE_PREFIX_PATH=/opt/gcc-arm -DCMAKE_TOOLCHAIN_FILE=../bluepill-cmsis/cmake/arm-none-eabi.cmake -DCONFIG=bluepill_config ..
1. make
