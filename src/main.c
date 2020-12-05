/*
 * Ledblink is an example hack for the BitLoom framework.  It implements a
 * simple task that blinks with a LED.  The LED can be controlled using
 * commands sent over UART.
 *
 * Copyright (c) 2020. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "hal/i2c.h"
#include "hal/timer.h"
#include "core/scheduler.h"
#include "core/uart.h"
#include "config/port_config.h"
#include "blinktask.h"
#include "ledcontrol.h"
#include "hmc5883l.h"

int main(void)
{
    timer_init();
    schedule_init();
    port_init();
    uart_init();
    i2c_init();
    hmc_driver_init();

    // Task initializations
    blink_task_init(schedule_add_task(240, 0, blink_task_run));
    ledcontrol_init(schedule_add_task(10, 0, ledcontrol_run));

    schedule_start();
    blink_task_enable_blink();

    while(1)
    {
        schedule_run();
    }
    return(0);
}
