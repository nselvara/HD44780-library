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

#if defined(USE_HAL_XILINX)
extern const lcd_hal_t lcd_hal_xilinx;
#define DEFAULT_HAL &lcd_hal_xilinx
#elif defined(USE_HAL_SIM)
extern const lcd_hal_t lcd_hal_sim;
#define DEFAULT_HAL &lcd_hal_sim
#else
extern const lcd_hal_t lcd_hal_mock;
#define DEFAULT_HAL &lcd_hal_mock
#endif

void lcd_init_with_default_hal(void) {
    lcd_hal_set_backend(DEFAULT_HAL);
    // user must call lcd_init() afterwards if needed
}
