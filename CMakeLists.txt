cmake_minimum_required(VERSION 3.15)
project(HD44780-library C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Option to set HAL backend
set(HD44780_HAL "mock" CACHE STRING "HAL backend implementation (mock, sim, xilinx)")

# Include headers
include_directories(include)

# Add subdirectories
add_subdirectory(src)

# Unit Tests
enable_testing()
add_executable(lcd_test tests/lcd_test.c)
target_link_libraries(lcd_test hd44780_lcd)
add_test(NAME unit_test COMMAND lcd_test)

# Demos
add_executable(lcd_demo_mock demo/lcd_demo_mock.c)
target_link_libraries(lcd_demo_mock hd44780_lcd)

add_executable(lcd_demo_xilinx demo/lcd_demo_xilinx.c)
target_link_libraries(lcd_demo_xilinx hd44780_lcd)
