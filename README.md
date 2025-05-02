[![Build Status](https://github.com/nselvara/HD44780-library/actions/workflows/ci.yml/badge.svg)](https://github.com/nselvara/HD44780-library/actions/workflows/ci.yml)
[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)
[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](#)

# HD44780 LCD Library for MicroBlaze (and Beyond)

A modern, simulation-capable C library to control HD44780-compatible character LCDs (like 4x16) via an 8-bit parallel interface.

Designed for Xilinx MicroBlaze but adaptable to any embedded platform. Includes full host-side simulation, unit tests, and printf-style rendering support.

---

## ✨ Features

- 8-bit GPIO interface using simple HAL
- Custom `lcd_print_custom()` and standard `lcd_print_std()` versions
- 4x16 LCD simulation with terminal output
- Testable on host system without hardware
- Cursor control, special character translation
- Unit-tested & CI-ready

---

## 🛠 Build & Test Instructions

### ✅ Prerequisites

- C compiler (e.g. GCC or Clang)
- CMake ≥ 3.10
- Git (for cloning)

### 🔧 Building (with CMake)

```bash
git clone https://github.com/nselvara/HD44780-library.git
cd HD44780-library
mkdir build && cd build
cmake .. -DUSE_SIMULATION=ON
make
```

### ▶️ Running the Demo

```bash
./lcd_demo
```

You'll see simulated output like:

```
----- LCD STATE -----
CPU Temp: 37.80°C
Hello, World!
                
----------------------
```

### ✅ Running Unit Tests

```bash
./lcd_test
```

All tests run with simulated LCD buffer and assert correctness.

---

## 🔌 Platform Abstraction (HAL)

To use on your own hardware:

Implement two platform-specific functions in a new file:

```c
void lcd_gpio_write(uint8_t data, uint8_t rs, uint8_t rw, uint8_t en);
void lcd_delay_ms(uint32_t ms);
```

For example, for Xilinx MicroBlaze you'd call `XGpio_DiscreteWrite()` and `usleep()`.

---

## 🧪 Two `lcd_print_xy()` Implementations

```c
lcd_print_custom("Temp: %d°C", 27);  // My own implementation (it uses less resources)
lcd_print_std("Temp: %.2f°C", 27.5); // Standard via vsnprintf
```

Both are available and interchangeable.

---

## 🧩 File Structure

```
include/         → Public headers
src/             → Core source files and simulation HAL
tests/           → Unit tests with simulated LCD output
examples/        → CLI demo app with snapshot support
.github/         → GitHub Actions CI
```

---

## 🧾 License

This project is licensed under the **LGPL v3.0**.  
You can use this library in both open and closed-source projects, as long as you publish modifications to the library itself.

See [LICENSE](./LICENSE) for full terms.

---
