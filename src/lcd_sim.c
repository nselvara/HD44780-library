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
#include "lcd_hal.h"
#include "lcd_snapshot.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define LCD_COLS 16
#define LCD_ROWS 4

char lcd_buffer[LCD_ROWS][LCD_COLS + 1]; // +1 for null-termination
int cursor_row = 0;
int cursor_col = 0;

void lcd_gpio_write(uint8_t data, uint8_t rs, uint8_t rw, uint8_t en)
{
    if (en == 1 && rs == 1) {
        char ch = (char)(data >> 4);
        if (cursor_row >= 0 && cursor_row < LCD_ROWS && cursor_col >= 0 && cursor_col < LCD_COLS) {
            lcd_buffer[cursor_row][cursor_col] = ch;
            cursor_col++;
            if (cursor_col >= LCD_COLS) {
                cursor_col = 0;
                cursor_row = (cursor_row + 1) % LCD_ROWS;
            }
        }
    }
}

void lcd_delay_ms(uint32_t ms)
{
    (void)ms; // No delay needed in simulation
}

void lcd_snapshot(void)
{
    printf("\n----- LCD STATE -----\n");
    for (int i = 0; i < LCD_ROWS; i++) {
        printf("%.*s\n", LCD_COLS, lcd_buffer[i]);
    }
    printf("----------------------\n\n");
}

void lcd_reset_simulation(void)
{
    for (int i = 0; i < LCD_ROWS; ++i) {
        for (int j = 0; j < LCD_COLS; ++j) {
            lcd_buffer[i][j] = ' ';
        }
        lcd_buffer[i][LCD_COLS] = '\0'; // ensure null termination
    }
    cursor_row = 0;
    cursor_col = 0;
}

const char *lcd_get_line(int row)
{
    int adjusted_row = row - 1;

    if (adjusted_row >= 0 && adjusted_row < LCD_ROWS) {
        printf("DEBUG: lcd_get_line(%d) = '", adjusted_row);

        // First check if we need to return the original buffer
        if (lcd_buffer[adjusted_row][0] == ' ' || lcd_buffer[adjusted_row][0] == '\0') {
            // Return the original buffer for all-spaces/empty lines
            return lcd_buffer[adjusted_row];
        }

        // Otherwise we need to trim spaces - only declare the buffer when needed
        static char trimmed_buffer[LCD_COLS + 1]; // Must be static since we return it

        // Copy the buffer so we can modify it
        memcpy(trimmed_buffer, lcd_buffer[adjusted_row], LCD_COLS + 1);

        // Trim trailing spaces for content lines
        int end = LCD_COLS - 1;
        while (end >= 0 && trimmed_buffer[end] == ' ') {
            trimmed_buffer[end--] = '\0';
        }
        return trimmed_buffer;
    }
    return "";
}
