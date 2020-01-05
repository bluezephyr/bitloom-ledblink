/*
 * Port configuration for the AVR for the ledblink hack
 *
 * Copyright (c) 2018. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef PORT_CONFIG_H
#define PORT_CONFIG_H

#include <avr/io.h>
#include <stdint.h>

/*
 * LED config
 *
 * The following needs to be set.
 *
 * LED_DDR  - DDR for the LED
 * LED_PORT - Port for the LED
 * LED      - The pin where the LED is connected.
 */
#define LED_PORT    PORTB
#define LED_DDR     DDRB
#define LED_GREEN   PB1

void port_init(void);

#endif  // PORT_CONFIG_H
