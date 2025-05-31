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
#include <stdint.h>

// Stub functions: do nothing
static void stub_init(void) {}
static void stub_send_command(uint8_t value) {}
static void stub_send_data(uint8_t value) {}
static void stub_delay_ms(uint32_t ms) { (void)ms; }
static void stub_deinit(void) {}

// Expose stub HAL
const lcd_hal_t lcd_hal_stub = {
    .init = stub_init,
    .send_command = stub_send_command,
    .send_data = stub_send_data,
    .delay_ms = stub_delay_ms,
    .deinit = stub_deinit
};
