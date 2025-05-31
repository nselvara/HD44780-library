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

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

void lcd_itoa(int num, char *buf, size_t bufsize)
{
    if (bufsize == 0)
        return;
    snprintf(buf, bufsize, "%d", num);
}

const char *lcd_hex_to_ascii(uint32_t hex, char *buf, size_t bufsize)
{
    if (bufsize < 9) {
        snprintf(buf, bufsize, "%X", hex & 0xFFFFFFFF);
    } else {
        snprintf(buf, 9, "%08X", hex);
    }
    return buf;
}
