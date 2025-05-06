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
#include "lcd_hal_sim.h"
#include "lcd_snapshot.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    #define usleep(x) Sleep((x) / 1000)
#else
    #include <unistd.h>
#endif

#define LCD_ROWS 4
#define LCD_COLS 16

static char lcd_buffer[LCD_ROWS][LCD_COLS + 1];
static int cursor_row = 0;
static int cursor_col = 0;

static void sim_init(void) {
    memset(lcd_buffer, ' ', sizeof(lcd_buffer));
    for (int i = 0; i < LCD_ROWS; i++)
        lcd_buffer[i][LCD_COLS] = '\0';
    cursor_row = 0;
    cursor_col = 0;
}

static void sim_send_command(uint8_t cmd) {
    if (cmd == 0x01) { // clear
        sim_init();
    } else if (cmd == 0x02) { // home
        cursor_row = 0;
        cursor_col = 0;
    } else if ((cmd & 0x80) == 0x80) {
        uint8_t addr = cmd & 0x7F;
        if (addr < 0x10) cursor_row = 0, cursor_col = addr;
        else if (addr < 0x50 && addr >= 0x40) cursor_row = 1, cursor_col = addr - 0x40;
        else if (addr < 0x20 && addr >= 0x10) cursor_row = 2, cursor_col = addr - 0x10;
        else if (addr < 0x60 && addr >= 0x50) cursor_row = 3, cursor_col = addr - 0x50;
    }
}

static void sim_send_data(uint8_t data) {
    if (cursor_row < LCD_ROWS && cursor_col < LCD_COLS)
        lcd_buffer[cursor_row][cursor_col++] = (char)data;
    if (cursor_col >= LCD_COLS) {
        cursor_col = 0;
        cursor_row = (cursor_row + 1) % LCD_ROWS;
    }
}

static void sim_delay(uint32_t ms) {
    (void)ms; // no-op
}

static void sim_deinit(void) {}

// NOTE: Don't move it anywhere else!
const lcd_hal_t lcd_hal_sim = {
    .init = sim_init,
    .send_command = sim_send_command,
    .send_data = sim_send_data,
    .delay_ms = sim_delay,
    .deinit = sim_deinit
};

// Optional extra utils
void lcd_snapshot(void) {
    printf("\n=== LCD SNAPSHOT ===\n");
    for (int i = 0; i < LCD_ROWS; ++i)
        printf("%.*s\n", LCD_COLS, lcd_buffer[i]);
    printf("====================\n");
}

void lcd_draw_bar(uint8_t row, uint8_t filled_cols, uint8_t total_cols) {
    lcd_set_cursor(row, 1);
    for (uint8_t i = 0; i < total_cols; ++i)
        lcd_write_char(i < filled_cols ? 0xFF : '-');
}

void lcd_scroll_left(void) {
    for (int r = 0; r < LCD_ROWS; ++r) {
        memmove(&lcd_buffer[r][0], &lcd_buffer[r][1], LCD_COLS - 1);
        lcd_buffer[r][LCD_COLS - 1] = ' ';
    }
}
