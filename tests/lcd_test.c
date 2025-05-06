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

void setUp(void) {
    // Optional: init/reset mock LCD
}

void tearDown(void) {
    // Optional: cleanup/reset
}

void test_lcd_itoa_should_convert_positive_integers_to_string(void) {
    char buffer[12];
    lcd_itoa(1234, buffer, 10);
    TEST_ASSERT_EQUAL_STRING("1234", buffer);
}

void test_lcd_itoa_should_convert_negative_integers_to_string(void) {
    char buffer[12];
    lcd_itoa(-1234, buffer, 10);
    TEST_ASSERT_EQUAL_STRING("-1234", buffer);
}

void test_lcd_itoa_should_convert_zero_to_string(void) {
    char buffer[12];
    lcd_itoa(0, buffer, 10);
    TEST_ASSERT_EQUAL_STRING("0", buffer);
}

void test_lcd_itoa_should_handle_base_16(void) {
    char buffer[12];
    lcd_itoa(255, buffer, 10);
    TEST_ASSERT_EQUAL_STRING("255", buffer);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_lcd_itoa_should_convert_positive_integers_to_string);
    RUN_TEST(test_lcd_itoa_should_convert_negative_integers_to_string);
    RUN_TEST(test_lcd_itoa_should_convert_zero_to_string);
    RUN_TEST(test_lcd_itoa_should_handle_base_16);

    return UNITY_END();
}
