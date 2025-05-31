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

/*
 * HD44780 Simulation HAL
 *
 * Emulates an HD44780-compatible LCD for testing.
 * Handles commands like clear display, return home, and set DDRAM address.
 */

#include "lcd_hal.h"
#include "lcd_sim.h"

#include <string.h>
#include <stdint.h>
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    #define usleep(x) Sleep((x) / 1000)
#else
    #include <unistd.h>
#endif
 
#define LCD_ROWS 4
#define LCD_COLS 16

extern char lcd_buffer[LCD_ROWS][LCD_COLS + 1];
extern int cursor_row;
extern int cursor_col;

static void sim_init(void) {
    lcd_reset_simulation();
    printf("LCD SIM: After init buffer [0]: '%s'\n", lcd_get_line(0));
}

static void sim_send_command(uint8_t cmd) {
    if (cmd == 0x01) { // Clear display
        lcd_reset_simulation(); // Use the centralized function
    } else if (cmd == 0x02) { // Return home
        cursor_row = 0;
        cursor_col = 0;
    } else if ((cmd & 0x80) == 0x80) { // Set DDRAM address
        uint8_t addr = cmd & 0x7F;
        if (addr < 0x10) {
            cursor_row = 0;
            cursor_col = addr;
        } else if (addr >= 0x40 && addr < 0x50) {
            cursor_row = 1;
            cursor_col = addr - 0x40;
        } else if (addr >= 0x10 && addr < 0x20) {
            cursor_row = 2;
            cursor_col = addr - 0x10;
        } else if (addr >= 0x50 && addr < 0x60) {
            cursor_row = 3;
            cursor_col = addr - 0x50;
        }
    }
}

static void sim_send_data(uint8_t val) {
    if (cursor_row < LCD_ROWS && cursor_col < LCD_COLS) {
        lcd_buffer[cursor_row][cursor_col++] = (char)val;
        printf("LCD SIM: Writing '%c' at [%d][%d]\n", (char)val, cursor_row, cursor_col-1);
        if (cursor_col >= LCD_COLS) {
            cursor_col = 0;
            cursor_row = (cursor_row + 1) % LCD_ROWS;
        }
    }
}

static void sim_delay(uint32_t ms) {
    (void)ms;
}

static void sim_deinit(void) {
    // Optional cleanup
}

const lcd_hal_t lcd_hal_sim = {
    .init = sim_init,
    .send_command = sim_send_command,
    .send_data = sim_send_data,
    .delay_ms = sim_delay,
    .deinit = sim_deinit
};
