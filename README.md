# BitLoom LEDblink
This repository contains a small hack that blinks a LED using the BitLoom framework.  The program is implemented in C and targets different small embedded
microcontrollers; at the moment AVR (ATMega328P and ATTiny).

## LEB Blink
The LED Blink (ledblink) hack is a trivial program that flashes a LED on and off at a regular interval (240 ms).  The program has one task (blink_task) that turns on and off the LED using the pin_digital_io interface.  The current implementation runs on an ATMega328P and utilizes the HAL declared by the BitLoom core.  The timer interface and the IO interface are implemented by the submodule bitloom-avr.  The port configuration is a custom implementation for this specific hack.

To build the program for AVR, follow the steps below.  It is assumed that the an AVR cross compilation toolchain is installed on the computer.  The type of programmer to flash the board can be configured in the avr-gcc-toolchain.cmake file (USBTinyISP or AVRISP).

 1. git clone https://github.com/bluezephyr/bitloom-ledblink.git
 1. cd bitloom-ledblink
 1. git submodule update --init
 1. mkdir build
 1. cd build
 1. cmake -DCMAKE_TOOLCHAIN_FILE=../bitloom-avr/avr-gcc-toolchain.cmake -DCONFIG=avr_config ..
 1. make
 1. make flash

The program will then be flashed to the MCU and the LED connected to PIN PB1 will start to blink.

