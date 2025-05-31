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

/* Mock Xilinx GPIO header for Windows development */
#ifndef XGPIO_H
#define XGPIO_H

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned long UINTPTR;

typedef struct {
    u32 BaseAddress;
    int IsReady;
} XGpio;

typedef struct {
    u16 DeviceId;
    UINTPTR BaseAddress;
} XGpio_Config;

/* Mock function declarations */
#define XGpio_Initialize(InstancePtr, DeviceId) (0)
#define XGpio_DiscreteWrite(InstancePtr, Channel, Data) ((void)0)
#define XGpio_SetDataDirection(InstancePtr, Channel, DirectionMask) ((void)0)

#define XPAR_GPIO_0_DEVICE_ID 0

#endif /* XGPIO_H */
