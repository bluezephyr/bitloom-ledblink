/*
 * This task reads compass data from a HMC5883L device and outputs the
 * result on UART.
 *
 * Copyright (c) 2020. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include <core/uart.h>
#include <string.h>
#include "compass.h"

#define DATA_LEN 9

static struct compass_t
{
    uint8_t data[DATA_LEN];
} self;

void compass_init (uint8_t taskId)
{
    (void)taskId;
    memcpy(self.data, "\rXX YY ZZ", DATA_LEN);
}

void compass_run (void)
{
    uart_write(self.data, DATA_LEN);
}


