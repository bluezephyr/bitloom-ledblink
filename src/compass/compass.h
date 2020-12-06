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
#ifndef COMPASS_H
#define COMPASS_H

#include <stdint.h>

/*
 * Init function. Must be called before the scheduler is started.
 */
void compass_init (uint8_t taskId);

/*
 * Run function for the task. Called by the scheduler.
 */
void compass_run (void);

#endif // COMPASS_H
