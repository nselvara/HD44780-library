set(HD44780_CORE
    lcd.c
    lcd_features.c
    lcd_backend.c
    lcd_utils_safe.c
    lcd_hal.c
)

add_library(hd44780_lcd ${HD44780_CORE})
target_include_directories(hd44780_lcd PUBLIC ${CMAKE_SOURCE_DIR}/include)
