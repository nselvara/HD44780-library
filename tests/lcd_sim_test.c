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
#include "lcd_sim.h"  // for lcd_buffer
#include <string.h>
#include <stdio.h>
#include <assert.h>

extern void lcd_snapshot(void);
extern void lcd_reset_simulation(void);

void test_printing_text(void) {
    lcd_reset_simulation();
    lcd_init();
    lcd_write_at("Hello", 1, 1);
    lcd_print_custom("World");

    lcd_snapshot(); // visually inspect

    // Assert "Hello World" is printed on row 1
    assert(strncmp(lcd_buffer[0], "Hello World", 11) == 0);
}

void test_number_format(void) {
    lcd_reset_simulation();
    lcd_init();
    lcd_write_at("Value:", 2, 1);
    lcd_print_custom(" %d", 42);

    lcd_snapshot();
    assert(strstr(lcd_buffer[1], "42") != NULL);
}

int main(void) {
    test_printing_text();
    test_number_format();
    printf("All simulated LCD tests passed.\n");
    return 0;
}
