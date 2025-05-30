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

#ifndef LCD_HAL_H_
#define LCD_HAL_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void (*init)(void);
    void (*send_command)(uint8_t value);
    void (*send_data)(uint8_t value);
    void (*delay_ms)(uint32_t ms);
    void (*deinit)(void);
} lcd_hal_t;

void lcd_hal_set_backend(const lcd_hal_t *backend);
const lcd_hal_t *lcd_hal_get_active(void);

#ifdef __cplusplus
}
#endif

#endif // LCD_HAL_H_
