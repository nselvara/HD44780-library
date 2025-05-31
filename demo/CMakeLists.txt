if(HD44780_USE_HAL_MOCK)
  add_executable(lcd_demo_mock lcd_demo_mock.c)
  target_link_libraries(lcd_demo_mock hd44780_lcd)
endif()

if(HD44780_USE_HAL_XILINX)
  add_executable(lcd_demo_xilinx lcd_demo_xilinx.c)
  target_link_libraries(lcd_demo_xilinx hd44780_lcd)
endif()
