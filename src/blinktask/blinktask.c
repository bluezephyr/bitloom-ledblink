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

typedef struct
{
    bool led_activated;
    bool blinking_enabled;
} blinktask_t;
static blinktask_t self;

void blink_task_init (uint8_t taskid)
{
    (void)taskid;
    self.led_activated = false;
    self.blinking_enabled = false;
}

void blink_task_enable_blink(void)
{
    self.blinking_enabled = true;
    self.led_activated = true;
}

void blink_task_disable_blink(void)
{
    self.blinking_enabled = false;
    self.led_activated = false;
}

void blink_task_run (void)
{
    if (self.blinking_enabled)
    {
        self.led_activated = !self.led_activated;
    }

    if (self.led_activated)
    {
        pin_digital_io_write_high(LED_GREEN);
    }
    else
    {
        pin_digital_io_write_low(LED_GREEN);
    }
}


