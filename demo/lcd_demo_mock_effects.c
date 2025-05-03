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

extern const lcd_hal_t LCD_HAL_MOCK;

int main(void) {
    lcd_hal_set_backend(&LCD_HAL_MOCK);
    lcd_init();

    lcd_write("Welcome!");
    lcd_set_cursor(2, 1);
    lcd_print_custom("Temp: %dC", 25);
    lcd_set_cursor(3, 1);
    lcd_draw_bar(3, 8, 16);

    lcd_snapshot();

    sleep(2);
    lcd_scroll_left();
    lcd_snapshot();

    return 0;
}
