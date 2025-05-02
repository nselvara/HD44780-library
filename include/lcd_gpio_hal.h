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

#ifndef LCD_GPIO_HAL_H_
#define LCD_GPIO_HAL_H_

#include <stdint.h>

// These functions should be implemented per-platform
void lcd_gpio_write(uint8_t data, uint8_t rs, uint8_t rw, uint8_t en);
void lcd_delay_ms(uint32_t ms);

#endif // LCD_GPIO_HAL_H_
