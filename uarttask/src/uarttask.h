/*
 * This task receives information from UART and uses it to control a LED.
 *
 * Copyright (c) 2020. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 *
 */
#ifndef UARTTASK_H
#define UARTTASK_H

#include <stdint.h>

/*
 * Init function. Must be called before the scheduler is started.
 * The id is the task id and is pro
 */
void uart_task_init (uint8_t taskid);

/*
 * Run function for the task. Called by the scheduler.
 */
void uart_task_run (void);

#endif // UARTTASK_H
