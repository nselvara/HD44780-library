if (HD44780_USE_HAL_SIM)
    target_sources(hd44780_lcd PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lcd_hal_sim.c
        ${CMAKE_SOURCE_DIR}/src/lcd_sim.c
    )
    target_compile_definitions(hd44780_lcd PUBLIC LCD_HAL_SIM)
elseif (HD44780_USE_HAL_XILINX)
    target_sources(hd44780_lcd PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lcd_hal_xilinx_gpio.c
    )
    target_compile_definitions(hd44780_lcd PUBLIC LCD_HAL_XILINX)
elseif (HD44780_USE_HAL_MOCK)
    target_sources(hd44780_lcd PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lcd_hal_mock.c
    )
    target_compile_definitions(hd44780_lcd PUBLIC LCD_HAL_MOCK)
elseif (HD44780_USE_HAL_STUB)
    target_sources(hd44780_lcd PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lcd_hal_stub.c
    )
    target_compile_definitions(hd44780_lcd PUBLIC LCD_HAL_STUB)
else()
    message(FATAL_ERROR "No valid HAL implementation selected!")
endif()
