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
#include "Unity.h"
#include <string.h>

extern const lcd_hal_t LCD_HAL_MOCK;

TEST(test_lcd_cursor_set) {
    lcd_hal_set_backend(&LCD_HAL_MOCK);
    lcd_init();
    lcd_set_cursor(2, 5);
    // Visual check (mock logs)
}

TEST(test_lcd_safe_itoa) {
    char buf[8];
    lcd_itoa(-123, buf, sizeof(buf));
    ASSERT_STR("-123", buf);

    lcd_itoa(999999, buf, 4);
    ASSERT_STR("999", buf); // truncated, no overflow
}

TEST(test_lcd_hex_output) {
    char hexbuf[9];
    lcd_hex_to_ascii(0xDEADBEEF, hexbuf, sizeof(hexbuf));
    ASSERT_STR("DEADBEEF", hexbuf);
}

TEST(test_lcd_custom_printf_numbers) {
    lcd_hal_set_backend(&LCD_HAL_MOCK);
    lcd_print_custom("Int:%d Hex:%x", 42, 255);
}
