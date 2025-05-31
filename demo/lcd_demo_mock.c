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
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
    #define sleep(x) Sleep((x)*1000)
#else
    #include <unistd.h>
#endif

extern const lcd_hal_t lcd_hal_mock;

int main(void) {
    // Set the backend to the mock HAL for simulation/printing
    lcd_hal_set_backend(&lcd_hal_mock);

    // Initialize the LCD
    lcd_init();

    // --- BASIC USAGE ---
    lcd_write_at("Welcome to", 1, 1);
    lcd_write_at("HD44780 Demo", 2, 1);

    // Pause and snapshot the current state
    lcd_snapshot();
    sleep(1);

    // --- FORMATTED OUTPUT ---
    lcd_clear();
    lcd_write_at("Temp: ", 1, 1);
    lcd_print_custom("%d C", 27);

    lcd_set_cursor(2, 1);
    lcd_print_std("Voltage: %.2fV", 3.30);

    lcd_set_cursor(3, 1);
    lcd_print_custom("ID: 0x%X", 0xDEAD);

    lcd_snapshot();
    sleep(1);

    // --- GRAPHIC/ANIMATION ---
    lcd_set_cursor(4, 1);
    lcd_write("Loading:");

    for (int i = 1; i <= 2; ++i) {
        lcd_set_cursor(4, i);
        lcd_write_char('|');
        lcd_snapshot();
        
        #ifdef _WIN32
            Sleep(100); // 100ms delay for animation
        #else
            usleep(100000); // 100ms delay for animation
        #endif
    }

    lcd_set_cursor(4, 10);
    lcd_write(" Done!");

    lcd_snapshot();
    return 0;
}
