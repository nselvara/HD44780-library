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


#include "unity.h"
#include "lcd.h"
#include "lcd_hal.h"
#include "lcd_sim.h"

extern const lcd_hal_t lcd_hal_sim;

void setUp(void) {
    lcd_hal_set_backend(&lcd_hal_sim);
    lcd_init();
    lcd_reset_simulation();
}

void tearDown(void) {
    // optional cleanup
}

void test_lcd_write_and_snapshot_should_store_data_correctly(void) {
    lcd_write_at("Hello", 1, 1);
    const char *line = lcd_get_line(1);
    TEST_ASSERT_NOT_NULL(line);
    TEST_ASSERT_EQUAL_STRING("Hello", line);
}

void test_lcd_clear_should_empty_all_lines(void) {
    lcd_write_at("Test", 1, 1);
    lcd_clear();
    for (int i = 1; i <= 4; ++i) {
        const char *line = lcd_get_line(i);
        for (int j = 0; j < 16; ++j) {
            TEST_ASSERT_EQUAL_CHAR(' ', line[j]);
        }
    }
}

void test_lcd_set_cursor_bounds(void) {
    lcd_set_cursor(1, 20); // invalid col
    lcd_write_char('X');
    const char *line = lcd_get_line(1);
    TEST_ASSERT_NOT_EQUAL('X', line[15]); // should not write outside bounds
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_lcd_write_and_snapshot_should_store_data_correctly);
    RUN_TEST(test_lcd_clear_should_empty_all_lines);
    RUN_TEST(test_lcd_set_cursor_bounds);
    return UNITY_END();
}
