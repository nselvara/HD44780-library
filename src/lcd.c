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

#include "lcd.h"
#include <stdio.h>
#include <string.h>

void lcd_init(void) {
    lcd_command(LCD_CMD_FUNCTION_SET | LCD_8BIT_MODE | LCD_2LINE_MODE);
    lcd_command(LCD_CMD_DISPLAY_CONTROL | LCD_DISPLAY_ON);
    lcd_command(LCD_CMD_CLEAR_DISPLAY);
    lcd_command(LCD_CMD_ENTRY_MODE_SET | LCD_ENTRY_INCREMENT);
}

void lcd_clear(void) {
    lcd_command(LCD_CMD_CLEAR_DISPLAY);
    lcd_hal_delay_ms(2);
}

void lcd_home(void) {
    lcd_command(LCD_CMD_RETURN_HOME);
    lcd_hal_delay_ms(2);
}

void lcd_set_display(bool display_on, bool cursor_on, bool blink_on) {
    uint8_t cmd = LCD_CMD_DISPLAY_CONTROL;
    if (display_on) cmd |= LCD_DISPLAY_ON;
    if (cursor_on)  cmd |= LCD_CURSOR_ON;
    if (blink_on)   cmd |= LCD_BLINK_ON;
}

void lcd_set_entry_mode(bool increment, bool shift) {
    uint8_t cmd = LCD_CMD_ENTRY_MODE_SET;
    if (increment) cmd |= LCD_ENTRY_INCREMENT;
    if (shift)     cmd |= LCD_ENTRY_SHIFT;
    lcd_hal_send_command(cmd);
}

void lcd_set_function(bool data8bit, bool lines2, bool font5x10) {
    uint8_t cmd = LCD_CMD_FUNCTION_SET;
    if (data8bit)  cmd |= LCD_8BIT_MODE;
    if (lines2)    cmd |= LCD_2LINE_MODE;
    if (font5x10)  cmd |= LCD_FONT_5x10;
    lcd_hal_send_command(cmd);
}

void lcd_goto(uint8_t row, uint8_t col) {
    static const uint8_t ROW_OFFSETS[] = { 0x00, 0x40, 0x10, 0x50 };
    lcd_hal_send_command(0x80 | (col + ROW_OFFSETS[row % 4]));
}

void lcd_command(lcd_command_t cmd) {
    lcd_hal_send_command((uint8_t)cmd);
    lcd_hal_delay_ms(2);
}

void lcd_write(const char *str) {
    while (*str) {
        lcd_write_char(*str++);
    }
}

void lcd_write_at(const char *str, int row, int col) {
    lcd_set_cursor(row, col);
    lcd_write(str);
}

void lcd_write_char(char ch) {
    lcd_hal_send_data((uint8_t)lcd_translate_special_char(ch));
    lcd_hal_delay_ms(1);
}

void lcd_print_std(const char *format, ...) {
    char buffer[128];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    lcd_write(buffer);
}

void lcd_set_cursor(int row, int col) {
    static const uint8_t ROW_OFFSETS[] = { 0x00, 0x40, 0x10, 0x50 };
    lcd_command(LCD_CMD_SET_DDRAM_ADDR | (ROW_OFFSETS[row - 1] + col - 1));
}

char lcd_translate_special_char(char ch) {
    switch (ch) {
        case 'ä': return 0x84;
        case 'ö': return 0x94;
        case 'ü': return 0x9A;
        case '°': return 0xDF;
        default: return ch;
    }
}

void lcd_reverse_string(char *str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

void lcd_itoa(int num, char *buffer, size_t buffersize) {
    snprintf(buffer, buffersize, "%d", num);
}

const char* lcd_hex_to_ascii(uint32_t hex, char *buffer, size_t buffersize) {
    snprintf(buffer, buffersize, "%08X", hex);
    return buffer;
}

void lcd_print_custom(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case '%':
                    lcd_write_char('%');
                    break;
                case 'd':
                case 'i': {
                    int val = va_arg(args, int);
                    char buf[12];
                    lcd_itoa(val, buf, sizeof(buf));
                    lcd_write(buf);
                    break;
                }
                case 'u': {
                    unsigned int val = va_arg(args, unsigned int);
                    char buf[12];
                    lcd_itoa(val, buf, sizeof(buf));
                    lcd_write(buf);
                    break;
                }
                case 'x':
                case 'X': {
                    unsigned int val = va_arg(args, unsigned int);
                    char buf[9];
                    lcd_hex_to_ascii(val, buf, sizeof(buf));
                    lcd_write(buf);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    lcd_write_char(c);
                    break;
                }
                case 's': {
                    const char *str = va_arg(args, const char *);
                    lcd_write(str);
                    break;
                }
                case 'f': {
                    double val = va_arg(args, double);
                    int whole = (int)val;
                    int frac = abs((int)((val - whole) * 1000));
                    char buf[12];
                    lcd_itoa(whole, buf, sizeof(buf));
                    lcd_write(buf);
                    lcd_write_char('.');
                    lcd_itoa(frac, buf, sizeof(buf));
                    lcd_write(buf);
                    break;
                }
                default:
                    // unsupported format specifier, skip
                    break;
            }
        } else {
            lcd_write_char(*format);
        }
        format++;
    }

    va_end(args);
}
