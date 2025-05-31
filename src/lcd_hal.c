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

static const lcd_hal_t *active_backend = NULL;

const lcd_hal_t *lcd_hal_get_active(void) { return active_backend; }

void lcd_init_auto_or_manual(void)
{
    if (lcd_hal_get_active() == NULL) {
        lcd_init_with_default_hal(); // user-defined fallback
    }
}

void lcd_hal_set_backend(const lcd_hal_t *backend)
{
    active_backend = backend;
    if (backend && backend->init) {
        backend->init();
    }
}

void lcd_hal_send_command(uint8_t value)
{
    if (active_backend && active_backend->send_command) {
        active_backend->send_command(value);
    }
}

void lcd_hal_send_data(uint8_t value)
{
    if (active_backend && active_backend->send_data) {
        active_backend->send_data(value);
    }
}

void lcd_hal_delay_ms(uint32_t ms)
{
    if (active_backend && active_backend->delay_ms) {
        active_backend->delay_ms(ms);
    }
}

void lcd_hal_deinit(void)
{
    if (active_backend && active_backend->deinit) {
        active_backend->deinit();
    }
}
