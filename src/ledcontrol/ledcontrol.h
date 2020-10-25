/*
 * This task controls LED task by commands received on UART.
 *
 * Copyright (c) 2020. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 *
 */
#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <stdint.h>

/*
 * Init function. Must be called before the scheduler is started.
 * The id is the task id and is pro
 */
void ledcontrol_init (uint8_t taskid);

/*
 * Run function for the ledcontrol task. Called by the scheduler.
 */
void ledcontrol_run (void);

#endif // LEDCONTROL_H
