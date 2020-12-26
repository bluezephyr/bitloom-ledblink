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

#define OUTPUT_LEN 11

enum compass_state_t
{
    init,
    send_cra,
    send_crb,
    single_measurement,
    read_measurement,
    done,
    error
};

static struct compass_t
{
    uint8_t data[OUTPUT_LEN];
    enum compass_state_t state;
    enum i2c_op_result_t i2c_result;
    uint8_t counter;
    struct hmc_measurement_t measurements;
} self;

static void print_result(void);
static void print_error(void);

void compass_init (uint8_t taskId)
{
    (void)taskId;
    self.state = init;
    self.counter = 0;
    self.i2c_result = i2c_operation_ok;
    memcpy(self.data, "-- -- --   ", OUTPUT_LEN);
}

void compass_run (void)
{
    enum i2c_op_result_t i2c_result = get_i2c_result();

    switch (self.state)
    {
        case init:
            memcpy(self.data, "INIT STATE ", OUTPUT_LEN);
            if (self.counter++ > 10)
            {
                self.counter = 0;
                hmc_set_config_reg_A();
                self.state = send_cra;
            }
            break;
        case send_cra:
            if (i2c_result == i2c_operation_ok)
            {
                hmc_set_config_reg_B();
                self.state = send_crb;
            }
            break;
        case send_crb:
            if (i2c_result == i2c_operation_ok)
            {
                hmc_set_mode(hmc_single_mode);
                self.state = single_measurement;
            }
            break;
        case single_measurement:
            if (i2c_result == i2c_operation_ok)
            {
                hmc_read_measurement_registers();
                self.state = read_measurement;
            }
        case read_measurement:
            if (i2c_result == i2c_operation_ok)
            {
                hmc_get_measurement_data(&self.measurements);
                self.state = done;
            }
        case done:
            print_result();
            return;

        case error:
            break;
    }

    if (i2c_result > 0)
    {
        self.i2c_result = i2c_result;
        print_error();
    }
    else
    {
        print_result();
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
        case send_cra:
            memcpy(self.data, "SEND CRA   ", OUTPUT_LEN);
            break;
        case send_crb:
            memcpy(self.data, "SEND CRB   ", OUTPUT_LEN);
            break;
        case single_measurement:
            memcpy(self.data, "MEASURING  ", OUTPUT_LEN);
            break;
        case read_measurement:
            memcpy(self.data, "READ MEAS  ", OUTPUT_LEN);
            break;
        case done:
            sprintf(data_values, "\r%X%X%X", self.measurements.x, self.measurements.y, self.measurements.z);
            memcpy(self.data, data_values, OUTPUT_LEN);
            break;
        case error:
            memcpy(self.data, "\rERROR     ", OUTPUT_LEN);
            break;
    }
    uart_write(self.data, OUTPUT_LEN);
}


void print_error (void)
{
    char data_values[OUTPUT_LEN] = "           ";

    switch (self.i2c_result)
    {
        case i2c_operation_ok:
            memcpy(data_values, "OP OK      ", OUTPUT_LEN);
            break;
        case i2c_operation_processing:
            memcpy(data_values, "PROCESSING ", OUTPUT_LEN);
            break;
        case i2c_operation_start_error:
            memcpy(data_values, "START ERR  ", OUTPUT_LEN);
            break;
        case i2c_operation_repeated_start_error:
            memcpy(data_values, "REP START E", OUTPUT_LEN);
            break;
        case i2c_operation_sla_error:
            memcpy(data_values, "SLA ERR    ", OUTPUT_LEN);
            break;
        case i2c_operation_write_error:
            memcpy(data_values, "WRITE ERR  ", OUTPUT_LEN);
            break;
        case i2c_operation_read_error:
            memcpy(data_values, "READ ERR   ", OUTPUT_LEN);
            break;
        case i2c_operation_bus_error:
            memcpy(data_values, "BUS ERR    ", OUTPUT_LEN);
            break;
        case i2c_operation_error:
            memcpy(data_values, "OP ERR     ", OUTPUT_LEN);
            break;
    }
    uart_write(data_values, OUTPUT_LEN);
}