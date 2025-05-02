cmake_minimum_required(VERSION 3.10)
project(HD44780_LCD_Library C)

set(CMAKE_C_STANDARD 99)

# Options
option(USE_SIMULATION "Use simulation HAL" ON)

# Include directories
include_directories(include)

# Source files
set(LCD_SRC
    src/lcd.c
    src/lcd_sim.c
    src/lcd_hal_sim.c
    src/lcd_gpio_hal.c
)

if(USE_SIMULATION)
    list(APPEND LCD_SRC src/lcd_sim.c)
endif()

# Library
add_library(lcd STATIC ${LCD_SRC})

# Demo executable
add_executable(lcd_demo examples/demo.c)
target_link_libraries(lcd_demo PRIVATE lcd)

# Test executable
add_executable(lcd_test tests/lcd_sim_test.c)
target_link_libraries(lcd_test PRIVATE lcd)
