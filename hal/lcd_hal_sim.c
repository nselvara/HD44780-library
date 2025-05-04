/*
 * Copyright 2025 Selvarajah N.
 *
 * This file is part of the HD44780 LCD Library.
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library. If not, see <https://www.gnu.org/licenses/>.
 */

#include "lcd_hal.h"
#include <stdio.h>

static void sim_init(void) {
    printf("[HAL Sim] Initialized\n");
}

static void sim_command(uint8_t val) {
    printf("[HAL Sim] CMD: 0x%02X\n", val);
}

static void sim_data(uint8_t val) {
    printf("[HAL Sim] DATA: %c\n", val);
}

static void sim_delay(uint32_t ms) {
    printf("[HAL Sim] Delay %u ms\n", ms);
}

static void sim_deinit(void) {
    printf("[HAL Sim] Deinitialized\n");
}

const lcd_hal_t lcd_hal_sim = {
    .init = sim_init,
    .send_command = sim_command,
    .send_data = sim_data,
    .delay_ms = sim_delay,
    .deinit = sim_deinit,
};
