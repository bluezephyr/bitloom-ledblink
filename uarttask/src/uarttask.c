/*
 * UART Task.
 *
 * Copyright (c) 2020. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "uarttask.h"
#include "hal/uart.h"
#include "blinktask.h"

typedef struct
{
    uint8_t task_id;
} uart_task_t;
static uart_task_t self;

void uart_task_init (uint8_t taskid)
{
    // Set the task id
    self.task_id = taskid;
}

void uart_task_run (void)
{
    int8_t result;
    uint8_t data;

    // Read one byte of data from UART (if any)
    result = uart_read(&data, 1);

    if (result > 0)
    {
        // Process the data
        if (data == 'o')
        {
            blink_task_enable_blink();
        }
        else if (data == 'p')
        {
            blink_task_disable_blink();
        }
    }
    else
    {
        // Either no data or error
    }
}

