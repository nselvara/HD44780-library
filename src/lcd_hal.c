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

#include "lcd_hal.h"
#include <stddef.h>

static const lcd_hal_t *active_hal = NULL;

void lcd_hal_set_backend(const lcd_hal_t *backend) {
    if (backend && backend->init) {
        backend->init();
    }
    active_hal = backend;
}

const lcd_hal_t *lcd_hal_get_active(void) {
    return active_hal;
}

// Only initializes if not already set manually
void lcd_init_auto_or_manual(void) {
    if (lcd_hal_get_active() == NULL) {
        lcd_init_with_default_hal();
    }
    // assumes lcd_init() is safe to call regardless of backend
}
