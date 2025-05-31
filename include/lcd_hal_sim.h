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

#ifndef LCD_HAL_SIM_H_
#define LCD_HAL_SIM_H_

#include "lcd_hal.h"

extern const lcd_hal_t lcd_hal_sim;

void lcd_snapshot(void);
void lcd_draw_bar(uint8_t row, uint8_t filled_cols, uint8_t total_cols);
void lcd_scroll_left(void);

#endif // LCD_HAL_SIM_H_
