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

#ifndef LCD_FEATURES_H_
#define LCD_FEATURES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void lcd_define_char(uint8_t location, const uint8_t bitmap[8]);
void lcd_scroll_left(void);
void lcd_scroll_right(void);
void lcd_draw_bar(uint8_t row, uint8_t val, uint8_t max);

#ifdef __cplusplus
}
#endif

#endif
