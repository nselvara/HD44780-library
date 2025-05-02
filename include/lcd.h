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

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// LCD Commands
typedef enum {
    LCD_CMD_CLEAR = 0x01,
    LCD_CMD_HOME = 0x02,
    LCD_CMD_ENTRY_MODE = 0x06,
    LCD_CMD_DISPLAY_OFF = 0x08,
    LCD_CMD_DISPLAY_ON = 0x0C,
    LCD_CMD_FUNCTION_SET = 0x38,
    LCD_CMD_FUNCTION_RESET = 0x30,
    LCD_CMD_CURSOR_SHOW_BLINK = 0x03,
    LCD_CMD_SET_CURSOR = 0x80
} lcd_command_t;

// Public API
void lcd_init(void);
void lcd_clear(void);
void lcd_command(lcd_command_t command);
void lcd_write(const char *str);
void lcd_write_at(const char *str, int row, int col);
void lcd_write_char(char ch);
void lcd_set_cursor(int row, int col);
/// @brief Custom printf-style LCD output (my own implementation)
void lcd_print_custom(const char *format, ...);
/// @brief Standard printf-style LCD output using vsnprintf (if you don't trust mine ;) )
void lcd_print_std(const char *format, ...);

// Internal Utilities
char lcd_translate_special_char(char ch);
void lcd_reverse_string(char *str);
void lcd_itoa(int num, char *buf, size_t bufsize);
const char* lcd_hex_to_ascii(uint32_t hex, char *buf, size_t bufsize);

// HAL hooks (must be implemented externally)
void lcd_hal_send_command(uint8_t value);
void lcd_hal_send_data(uint8_t value);
void lcd_hal_delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif // LCD_H_
