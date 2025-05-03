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

void lcd_define_char(uint8_t location, const uint8_t bitmap[8]) {
    location &= 0x07; // Only 8 locations (0-7)
    lcd_command(LCD_CMD_SET_CGRAM_ADDR | (location << 3));
    for (int i = 0; i < 8; i++) {
        lcd_hal_send_data(bitmap[i]);
    }
    lcd_command(LCD_CMD_SET_DDRAM_ADDR); // Return to DDRAM
}

void lcd_scroll_left(void) {
    lcd_command(LCD_CMD_CURSOR_SHIFT | 0x08);
}

void lcd_scroll_right(void) {
    lcd_command(LCD_CMD_CURSOR_SHIFT | 0x0C);
}

void lcd_draw_bar(uint8_t row, uint8_t val, uint8_t max) {
    const uint8_t WIDTH = 16;
    uint8_t blocks = (val * WIDTH) / max;
    lcd_set_cursor(row, 1);
    for (uint8_t i = 0; i < WIDTH; i++) {
        lcd_write_char(i < blocks ? 0xFF : ' ');
    }
}
