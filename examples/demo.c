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

int main(void) {
    lcd_init();
    lcd_write_at("'\n'CPU Temp:", 1, 1);
    lcd_print_custom("'\n'Temp: %d°C, ID: 0x%X", 25, 0xABCD);
    lcd_print_std("'\n'Pi: %.2f", 3.14159);
    lcd_write_at("'\n'Hello, World!", 2, 1);
    lcd_snapshot();  // Simulated output
    return 0;
}
