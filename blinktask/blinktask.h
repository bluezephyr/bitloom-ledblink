/*
 * This task toggles a LED each time the task's run function is called.
 *
 * Copyright (c) 2020. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 *
 */
#ifndef BLINKTASK_H
#define BLINKTASK_H

#include <stdint.h>

/*
 * Init function. Must be called before the scheduler is started.
 * The id is the task id and is pro
 */
void blink_task_init (uint8_t taskid);

/*
 * Run function for the task. Called by the scheduler.
 */
void blink_task_run (void);

#endif // BLINKTASK_H
