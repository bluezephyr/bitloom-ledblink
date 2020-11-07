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

const char infoText[] = "\rWelcome to the LED blinker.\n\r"
                        "Press o to start LED\n\r"
                        "Press p to stop LED\n\r"
                        "Press i to enter input mode\n\r"
                        "Press h to show this text\r\n";
const int16_t infoTextLen = sizeof(infoText);

typedef struct
{
    uint8_t taskId;
    bool sendInfoText;
    bool input_mode;
} led_control_t;
static led_control_t self;

void ledcontrol_init (uint8_t taskId)
{
    self.taskId = taskId;
    self.sendInfoText = true;
    self.input_mode = false;
}

void ledcontrol_run (void)
{
    int8_t result;
    uint8_t selection;

    // Read one byte of data from UART (if any)
    result = uart_read(&selection, 1);

    if (result > 0)
    {
        if (self.input_mode)
        {
            if (selection == 0x1B)
            {
                self.input_mode = false;
                uart_write((uint8_t*)"\r\nNormal mode\r\n", 15);
            }
            else
            {
                uart_write(&selection, 1);
            }
            selection = 0;
        }
        else
        {
            switch (selection)
            {
                case 'h':
                    self.sendInfoText = true;
                    break;
                case 'o':
                    blink_task_enable_blink();
                    break;
                case 'p':
                    blink_task_disable_blink();
                    break;
                case 'i':
                    self.input_mode = true;
                    uart_write((uint8_t*)"Input mode (press ESC to exit)\r\n", 32);
                default:
                    // Ignore other
                    break;
            }
        }
    }
    else
    {
        // Either no data or error
    }

    if (self.sendInfoText)
    {
        uart_write((uint8_t*)infoText, sizeof(infoText));
        self.sendInfoText = false;
    }
}
