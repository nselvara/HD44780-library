[![Build Status](https://github.com/nselvara/HD44780-library/actions/workflows/ci.yml/badge.svg)](https://github.com/nselvara/HD44780-library/actions/workflows/ci.yml)
[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)
[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](#)

# HD44780 LCD Library for Embedded Systems

A modular, cross-platform, embedded C library for controlling HD44780-compatible character LCD displays.  
Supports custom HAL backends, simulation, printf-style output, and flexible demos.

---

## Features

- 8-bit GPIO interface using simple HAL
- Lot of LCD features (cursor, clear, bar drawing, scrolling)
  - Custom `lcd_print_custom()` and standard `lcd_print_std()` versions
- 4x16 LCD simulation with terminal output
- Cursor control, special character translation
- Full unit test and demo integration
  - Testable on host system without hardware
- ANSI C (C99) and portable
- HAL-based architecture (simulation, Xilinx GPIO, mock, custom)
- CMake-based build system

---

## Build & Test Instructions

### Prerequisites

- CMake >= 3.14
- A C99-compatible compiler (GCC, Clang, etc.)
- Git (for cloning)

### Building (with CMake)

#### Usage

Clone the repository and select the HAL backend using the provided helper script:

```bash
git clone https://github.com/nselvara/HD44780-library.git
cd HD44780-library
python build_and_deploy.py [mock|stub|sim|xilinx]
```

Example:

```bash
python build_and_deploy.py mock
```

This will:

- Clean the build/ directory (if it exists)
- Configure CMake with the correct HAL flags
- Build the library and relevant demos/tests

Only one HAL can be enabled at a time. The script enforces this for you.

#### Demo Examples

| Demo Binary (Linus) | Demo Binary (Windows) | Description                          |
| ------------------- | --------------------- | ------------------------------------ |
| `lcd_demo_mock`     | `lcd_demo_mock.exe`   | Full-featured text/printf-style demo |
| `lcd_demo_xilinx`   | `lcd_demo_xilinx.exe` | Uses Xilinx GPIO HAL (if selected)   |

To run the mock demo (after building with `build_and_deploy.py mock`):

##### Windows

```powershell
.Build\demo\Debug\lcd_demo_mock.exe
```

##### Linux

```bash
./build/demo/lcd_demo_mock
```

##### Expected output

```terminal
[Mock HAL] Init
[Mock HAL] CMD 0x01
...
=== LCD SNAPSHOT ===
Welcome to
HD44780 Demo
...
====================
```

#### Using the Xilinx HAL

In your code to use the Xilinx GPIO backend:

```c
lcd_hal_set_backend(&lcd_hal_xilinx_gpio);
lcd_init();
```

Then to build using the Xilinx GPIO interface:

```bash
python build_and_deploy.py xilinx
```

Both are available and interchangeable.

### Run Unit Tests

Tests use the simulation or stub HAL and verify LCD state with assertions.

```bash
python build_and_deploy.py mock --test
```

or

```bash
python build_and_deploy.py sim --test
```

All tests run with simulated LCD buffer and assert correctness.

---

## Platform Abstraction (HAL)

To use on your own hardware:

Implement two platform-specific functions in a new file:

```c
void lcd_gpio_write(uint8_t data, uint8_t rs, uint8_t rw, uint8_t en);
void lcd_delay_ms(uint32_t ms);
```

For example, for Xilinx MicroBlaze you'd call `XGpio_DiscreteWrite()` and `usleep()`.

---

## Two `lcd_print_xy()` Implementations

```c
// My own implementation (it uses less resources, as it doesn't implement everything)
lcd_print_custom("Temp: %d°C", 27);
// Standard via vsnprintf
lcd_print_std("Temp: %.2f°C", 27.5);
```

---

## 🔧 API Overview

| Function                        | Description                                     | Category        |
| ------------------------------- | ----------------------------------------------- | --------------- |
| `lcd_init_with_default_hal()`   | Initializes the default HAL (selected by CMake) | Initialization  |
| `lcd_init_auto_or_manual()`     | Only sets HAL if one hasn't been set            | Initialization  |
| `lcd_write(char*)`              | Writes a string at current cursor position      | Basic Output    |
| `lcd_write_at(char*, row, col)` | Writes a string at specific position            | Basic Output    |
| `lcd_set_cursor(row, col)`      | Sets the cursor position                        | Cursor Control  |
| `lcd_print_custom(fmt, ...)`    | Lightweight printf-style formatted output       | Formatting      |
| `lcd_print_std(fmt, ...)`       | Standard printf with full formatting support    | Formatting      |
| `lcd_draw_bar(len, max)`        | Draws a progress bar                            | Graphics        |
| `lcd_scroll_left()`             | Scrolls display left                            | Display Control |
| `lcd_scroll_right()`            | Scrolls display right                           | Display Control |
| `lcd_clear()`                   | Clears display and homes cursor                 | Display Control |

---

## File Structure

```tree
📁 include/          → Public headers (lcd.h, config, features)
📁 src/              → Core implementation logic
📁 hal/              → Platform HAL implementations (mock, sim, xilinx)
📁 tests/            → Unit + simulation tests
📁 demo/             → Example programs using LCD
📁 .github/workflows → CI for build/test/release
```

---

## Project Structure

```tree
HD44780-library/
├── CMakeLists.txt
├── include/                # Public headers
│   └── lcd.h, lcd_hal.h, lcd_features.h, lcd_hal_xilinx_gpio.h
├── hal/                    # HAL implementations (sim, Xilinx, etc.)
│   └── lcd_hal_*.c
├── src/                    # Core implementation files
├── test/                   # Unit tests
├── demo/                   # Terminal simulation demo
├── docs/                   # (Generated by Doxygen)
├── .github/workflows/      # CI workflow
├── .clang-format
├── Doxyfile
└── README.md
```

## Xilinx MicroBlaze Example

To use this library in a Xilinx platform (e.g. with PLB GPIO):

```c
#include "lcd.h"
#include "lcd_hal_xilinx_gpio.h"

int main() {
    lcd_hal_set_backend(&lcd_hal_xilinx_gpio);
    lcd_init();
    lcd_write("Hello from FPGA!");
    while (1);
}
```

In Vivado SDK / Vitis:

- Link against compiled `.a` or include the source
- Set `XPAR_LCD_GPIO_DEVICE_ID` via `xparameters.h`

---

## License

This project is licensed under the **LGPL v3.0**.  
You can use this library in both open and closed-source projects, as long as you publish modifications to the library itself.

See [LICENSE](./LICENSE) for full terms.

### Third-Party Licenses

#### Unity Test Framework

The test framework used in this project, Unity, is licensed under the MIT License:

See [Unity LICENSE.txt](./third_party/unity/LICENSE.txt) for details.

#### AMD/Xilinx Embedded Software (embeddedsw)

This project uses components from Xilinx/AMD embeddedsw, which are licensed under the MIT License:

See [embeddedsw LICENSE.txt](./third_party/xilinx/embeddedsw/LICENSE.txt) for details.
