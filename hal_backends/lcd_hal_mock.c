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
#include <string.h>
#include <stdio.h>

#define LCD_ROWS 4
#define LCD_COLS 16

char lcd_buffer[LCD_ROWS][LCD_COLS + 1]; // +1 for null-terminator
static int cur_row = 0;
static int cur_col = 0;

static void mock_send_command(uint8_t val) {
    if (val == 0x01) { // Clear display
        for (int i = 0; i < LCD_ROWS; i++) {
            memset(lcd_buffer[i], ' ', LCD_COLS);
            lcd_buffer[i][LCD_COLS] = '\0';
        }
        cur_row = cur_col = 0;
    } else if (val >= 0x80 && val <= 0xFF) {
        uint8_t addr = val & 0x7F;
        static const uint8_t ROW_BASE[] = {0x00, 0x40, 0x10, 0x50};
        for (int i = 0; i < 4; ++i) {
            if (addr >= ROW_BASE[i] && addr < ROW_BASE[i] + LCD_COLS) {
                cur_row = i;
                cur_col = addr - ROW_BASE[i];
                break;
            }
        }
    }
}

static void mock_send_data(uint8_t ch) {
    if (cur_row < LCD_ROWS && cur_col < LCD_COLS) {
        lcd_buffer[cur_row][cur_col++] = ch;
    }
}

static void mock_delay(uint32_t ms) { (void)ms; }
static void mock_init(void) {}

void lcd_snapshot(void) {
    printf("\n=== LCD Snapshot ===\n");
    for (int i = 0; i < LCD_ROWS; i++) {
        printf("%.*s\n", LCD_COLS, lcd_buffer[i]);
    }
    printf("====================\n");
}

const lcd_hal_t LCD_HAL_MOCK = {
    .init = mock_init,
    .send_command = mock_send_command,
    .send_data = mock_send_data,
    .delay_ms = mock_delay
};
