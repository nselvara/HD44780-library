cmake_minimum_required(VERSION 3.16)
project(HD44780_LCD_Library C)

set(CMAKE_C_STANDARD 99)

# Optional: default to Debug build
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Library source files
set(LIB_SRC
    src/lcd.c
    src/lcd_backend.c
    src/lcd_hal.c
    src/lcd_features.c
    src/lcd_sim.c
    src/lcd_utils_safe.c
)

# Public include headers
include_directories(include)

# Create core library
add_library(hd44780_lcd STATIC ${LIB_SRC})

# ----------- Demo Targets ------------

# Mock Demo
add_executable(lcd_demo_mock demo/lcd_demo_mock.c)
target_sources(lcd_demo_mock PRIVATE hal/lcd_hal_mock.c)
target_link_libraries(lcd_demo_mock PRIVATE hd44780_lcd)

# Xilinx Demo
add_executable(lcd_demo_xilinx demo/lcd_demo_xilinx.c)
target_sources(lcd_demo_xilinx PRIVATE hal/lcd_hal_xilinx_gpio.c)
target_link_libraries(lcd_demo_xilinx PRIVATE hd44780_lcd)

# Optional: install target (if desired)
install(TARGETS hd44780_lcd DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

# ----------- Unit Test Support -----------

# Unity test framework
add_subdirectory(third_party/Unity)

# Unit Test: lcd_test.c
add_executable(lcd_test tests/lcd_test.c)
target_sources(lcd_test PRIVATE hal/lcd_hal_mock.c)
target_link_libraries(lcd_test PRIVATE hd44780_lcd unity)
target_include_directories(lcd_test PRIVATE third_party/Unity/src)

# Unit Test: lcd_sim_test.c
add_executable(lcd_sim_test tests/lcd_sim_test.c)
target_link_libraries(lcd_sim_test PRIVATE hd44780_lcd unity)
target_include_directories(lcd_sim_test PRIVATE third_party/Unity/src)

# ----------- Platform Defines -----------
if(WIN32)
  add_definitions(-DWIN32_LEAN_AND_MEAN)
endif()
