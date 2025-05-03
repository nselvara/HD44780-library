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

static const lcd_hal_t *lcd_hal = 0;

void lcd_hal_set_backend(const lcd_hal_t *backend) {
    lcd_hal = backend;
}

void lcd_hal_send_command(uint8_t value) { lcd_hal->send_command(value); }
void lcd_hal_send_data(uint8_t value)    { lcd_hal->send_data(value); }
void lcd_hal_delay_ms(uint32_t ms)       { lcd_hal->delay_ms(ms); }
