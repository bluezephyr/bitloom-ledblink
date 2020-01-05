/*
 * This task toggles a led each time the task's run function is called.
 *
 * Copyright (c) 2020. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include <stdbool.h>
#include "config/port_config.h"
#include "hal/pin_digital_io.h"
#include "blinktask.h"

// This id is given by the scheduler when the task is added.
static uint8_t blink_task_id = 0;
static bool led_activated;

void blink_task_init (uint8_t taskid)
{
    // Set the task id
    blink_task_id = taskid;
    led_activated = true;
}

void blink_task_run (void)
{
    led_activated = !led_activated;
    if (led_activated)
    {
        pin_digital_io_write_high(LED_GREEN);
    }
    else
    {
        pin_digital_io_write_low(LED_GREEN);
    }
}

