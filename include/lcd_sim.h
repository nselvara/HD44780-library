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

#ifndef LCD_SIM_H
#define LCD_SIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lcd_config.h" // for LCD_ROWS, LCD_COLS
extern char lcd_buffer[LCD_ROWS][LCD_COLS + 1];

void lcd_reset_simulation(void);
void lcd_snapshot(void);
void lcd_set_cursor(int row, int col);
const char *lcd_get_line(int row);

#ifdef __cplusplus
}
#endif

#endif
