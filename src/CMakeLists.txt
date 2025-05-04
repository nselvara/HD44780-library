# src/CMakeLists.txt

# Determine HAL backend
set(HAL_DIR ${CMAKE_SOURCE_DIR}/hal)
if(HD44780_HAL STREQUAL "mock")
    set(HAL_SRC ${HAL_DIR}/lcd_hal_mock.c)
elseif(HD44780_HAL STREQUAL "sim")
    set(HAL_SRC ${HAL_DIR}/lcd_hal_sim.c)
elseif(HD44780_HAL STREQUAL "xilinx")
    set(HAL_SRC ${HAL_DIR}/lcd_hal_xilinx_gpio.c)
else()
    message(FATAL_ERROR "Unknown HAL backend: ${HD44780_HAL}")
endif()

# Library definition
add_library(hd44780_lcd STATIC
    lcd.c
    lcd_backend.c
    lcd_features.c
    lcd_hal.c
    lcd_utils_safe.c
    ${HAL_SRC}
)

target_include_directories(hd44780_lcd PUBLIC ${CMAKE_SOURCE_DIR}/include)
