/*
 * LEDControl Task.
 *
 * Copyright (c) 2020. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include <stdbool.h>
#include "ledcontrol.h"
#include "blinktask.h"
#include "core/uart.h"

const char infoText[] = "Welcome to the LED blinker.";
const int16_t infoTextLen = sizeof(infoText);

typedef struct
{
    uint8_t taskId;
    bool sendInfo;
    uint8_t infoTextPos;
} led_control_t;
static led_control_t self;

void ledcontrol_init (uint8_t taskId)
{
    self.taskId = taskId;
    self.sendInfo = false;
    self.infoTextPos = 0;
}

void ledcontrol_run (void)
{
    int8_t result;
    uint8_t selection;

    // Read one byte of data from UART (if any)
    result = uart_read(&selection, 1);

    if (result > 0)
    {
        switch (selection)
        {
            case 'h':
                if (!self.sendInfo)
                {
                    self.sendInfo = true;
                    self.infoTextPos = 0;
                }
                break;
            case 'o':
                blink_task_enable_blink();
                break;
            case 'p':
                blink_task_disable_blink();
                break;
            default:
                // Ignore other
                break;
        }
    }
    else
    {
        // Either no data or error
    }

    if (self.sendInfo)
    {
        uint8_t* textToSend = (uint8_t*)infoText + self.infoTextPos;
        self.infoTextPos += uart_write(textToSend, infoTextLen-self.infoTextPos);
        if (self.infoTextPos == infoTextLen)
        {
            self.sendInfo = false;
        }
    }
}
