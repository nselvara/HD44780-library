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

#include "LCD_HAL_XILINX_GPIO.h"
#include "xgpio.h"
#include "xparameters.h"

static XGpio lcd_gpio;
static uint32_t gpio_channel = 1;
static uint32_t gpio_mask_data = 0;

static void xilinx_init(void) {
    XGpio_Initialize(&lcd_gpio, XPAR_LCD_GPIO_DEVICE_ID);
    XGpio_SetDataDirection(&lcd_gpio, gpio_channel, 0x00); // all outputs
}

static void xilinx_send_command(uint8_t cmd) {
    gpio_mask_data = (cmd & 0xF0) | 0x00; // RS = 0, EN = 0
    XGpio_DiscreteWrite(&lcd_gpio, gpio_channel, gpio_mask_data | 0x04); // EN = 1
    XGpio_DiscreteWrite(&lcd_gpio, gpio_channel, gpio_mask_data);        // EN = 0
}

static void xilinx_send_data(uint8_t data) {
    gpio_mask_data = (data & 0xF0) | 0x01; // RS = 1, EN = 0
    XGpio_DiscreteWrite(&lcd_gpio, gpio_channel, gpio_mask_data | 0x04); // EN = 1
    XGpio_DiscreteWrite(&lcd_gpio, gpio_channel, gpio_mask_data);        // EN = 0
}

static void xilinx_delay(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 8000; ++i); // crude delay for MicroBlaze
}

const lcd_hal_t LCD_HAL_XILINX_GPIO = {
    .init = xilinx_init,
    .send_command = xilinx_send_command,
    .send_data = xilinx_send_data,
    .delay_ms = xilinx_delay
};
