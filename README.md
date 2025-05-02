# HD44780 LCD Library for MicroBlaze

A lightweight and versatile C library for controlling HD44780-compatible 4x16 LCD displays using an 8-bit interface on Xilinx MicroBlaze platforms with PLB GPIO.

## Features

- 8-bit parallel communication
- Cursor positioning and formatted printing
- `lcd_print()` supports format strings: `%d`, `%u`, `%x`, `%f`, `%s`, `%c`
- Special character support: `ä`, `ö`, `ü`, `°`
- Internal utilities for number/string conversion

## Platform

- **Target:** Xilinx MicroBlaze (PLB)
- **Compiler:** GNU-C (via Xilinx SDK or Eclipse)
- **Dependencies:** Xilinx BSP (XGpio, MicroBlaze sleep, etc.)

## Example Usage

```c
lcd_init();
lcd_write_xy("Hello, World!", 1, 1);
lcd_print("Temp: %.1f C", 23.5);
```

## Pin Mapping

| MicroBlaze GPIO | LCD Pin |
| --- | --- |
| GPIO_LCD(11) | D7  |
| GPIO_LCD(10) | D6  |
| GPIO_LCD(09) | D5  |
| GPIO_LCD(08) | D4  |
| GPIO_LCD(07) | D3  |
| GPIO_LCD(06) | D2  |
| GPIO_LCD(05) | D1  |
| GPIO_LCD(04) | RS  |
| GPIO_LCD(03) | RW  |
| GPIO_LCD(02) | EN  |

## License

This project is licensed under the Apache License 2.0.  
See `LICENSE` for details.

```
Copyright 2017 Selvarajah N.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy at:

   http://www.apache.org/licenses/LICENSE-2.0
```

## Author

**Selvarajah N.**

- Initial Release: 08.02.2017
- Last Update: 17.12.2021
