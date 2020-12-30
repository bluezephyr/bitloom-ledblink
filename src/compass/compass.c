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

#include <core/uart.h>
#include <string.h>
#include <stdio.h>
#include "compass.h"
#include "hmc5883l.h"

#define OUTPUT_LEN  17
#define TIMEOUT    5

enum compass_state_t
{
    init,
    single_measurement,
    read_measurement,
    done,
    wait,
    error,
};

static struct compass_t
{
    uint8_t data[OUTPUT_LEN];
    enum compass_state_t state;
    enum i2c_op_result_t i2c_result;
    struct hmc_measurement_t measurements;
    enum hmc_op_result_t hmcResult;
    uint8_t timer;
} self;

static void print_result(void);

void compass_init (uint8_t taskId)
{
    (void)taskId;
    self.state = init;
    self.timer = TIMEOUT;
    memcpy(self.data, "-- -- --   ", OUTPUT_LEN);
}

void compass_run (void)
{
    switch (self.state)
    {
        case init:
            memcpy(self.data, "INIT STATE ", OUTPUT_LEN);
            hmc_set_config_reg_A(1 << HMC_CRA_MA0 | (1 << HMC_CRA_MA1) | (1 << HMC_CRA_DO2));
            hmc_set_config_reg_B(1 << HMC_CRB_GN0 | (1 << HMC_CRB_GN2));
            self.state = single_measurement;
            break;
        case single_measurement:
            hmc_start_single_measurement(&self.hmcResult);
            self.state = read_measurement;
            break;
        case read_measurement:
            if (self.hmcResult == hmc_operation_ok)
            {
                hmc_get_measurement_data(&self.measurements);
                self.state = done;
            }
            break;
        case done:
            print_result();
            self.timer = TIMEOUT;
            self.state = wait;
            return;
        case wait:
            if (self.timer-- == 0)
            {
                self.state = single_measurement;
            }
            return;
        case error:
            break;
    }
}

static void print_result(void)
{
    char data_values[OUTPUT_LEN] = "\rDONE      ";

    switch (self.state)
    {
        case init:
            memcpy(self.data, "INIT STATE ", OUTPUT_LEN);
            break;
        case single_measurement:
            memcpy(self.data, "MEASURING  ", OUTPUT_LEN);
            break;
        case read_measurement:
            memcpy(self.data, "READ MEAS  ", OUTPUT_LEN);
            break;
        case done:
            sprintf(data_values, "%4X %4X %4X\r\n", self.measurements.x, self.measurements.y, self.measurements.z);
            memcpy(self.data, data_values, OUTPUT_LEN);
            break;
        case error:
            memcpy(self.data, "\rERROR     ", OUTPUT_LEN);
            break;
    }
    uart_write(self.data, OUTPUT_LEN);
}
