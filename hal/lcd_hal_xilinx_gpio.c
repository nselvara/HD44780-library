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

// Add at the top of the file
#ifdef _WIN32
#include <windows.h> // For Sleep()
#else
#include <unistd.h> // For usleep()
#endif

#include "lcd_hal.h"
#include "xgpio.h"
#include "xparameters.h"

#define LCD_CHANNEL 1

static void xilinx_init(void) {
    XGpio_Initialize(&GPIO_LCD, XPAR_GPIO_0_DEVICE_ID);
}

static void xilinx_send_command(uint8_t val) {
    XGpio_DiscreteWrite(&GPIO_LCD, LCD_CHANNEL, val); // Replace with actual control signals
}

static void xilinx_send_data(uint8_t val) {
    XGpio_DiscreteWrite(&GPIO_LCD, LCD_CHANNEL, val); // Replace with actual control signals + RS=1
}

static void xilinx_delay(uint32_t ms) {
#ifdef _WIN32
    // Windows implementation
    Sleep(ms); // Windows uses milliseconds
#else
    // UNIX/Linux implementation
    usleep(ms * 1000); // usleep uses microseconds
#endif
}

static void xilinx_deinit(void) {}

const lcd_hal_t lcd_hal_xilinx = {
    .init = xilinx_init,
    .send_command = xilinx_send_command,
    .send_data = xilinx_send_data,
    .delay_ms = xilinx_delay,
    .deinit = xilinx_deinit,
};
