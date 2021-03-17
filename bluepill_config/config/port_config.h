/*
 * Port configuration for the Bluepill board for the ledblink hack
 *
 * Copyright (c) 2021. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#ifndef PORT_CONFIG_H
#define PORT_CONFIG_H

#include <stdint.h>

#define PC13        1u
#define LED_GREEN   PC13

void port_init(void);

#endif  // PORT_CONFIG_H
