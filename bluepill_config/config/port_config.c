/*
 * Port configuration for the Bluepill board for the ledblink hack
 *
 * Copyright (c) 2021. BlueZephyr
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */

#include "port_config.h"
#include "stm32f1xx.h"

void port_init(void)
{
    // 7.3.7 APB2 peripheral clock enable register (RCC_APB2ENR) in [1]
    // Enable APB2 peripheral clock for PORTC
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN);

    // 9.2.2 Port configuration register high (GPIOx_CRH) (x=A..G) in [1]
    // Set Pin 13
    // CNF1=0, CNF0=0: General Purpose output Push-Pull
    // MODE1=1, MODE0=1: Maximum output speed 50 MHz
    MODIFY_REG(GPIOC->CRH, GPIO_CRH_CNF13, GPIO_CRH_MODE13);

    // Active low - disable at start
    WRITE_REG(GPIOC->BSRR, GPIO_BSRR_BS13);
}
