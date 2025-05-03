option(BUILD_SHARED_LIBS "Build shared libraries instead of static" ON)
option(USE_XILINX_HAL "Use Xilinx GPIO HAL backend" OFF)
option(ENABLE_DEMO "Enable building example demos" ON)

# Install target
install(TARGETS hd44780
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

# pkg-config .pc file
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/hd44780.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/hd44780.pc
    @ONLY
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/hd44780.pc DESTINATION lib/pkgconfig)

# Library version
set_target_properties(hd44780 PROPERTIES
    VERSION 2.0.0
    SOVERSION 2
)

if(USE_XILINX_HAL)
    message(STATUS "Using Xilinx GPIO HAL")
    target_sources(hd44780 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/hal/LCD_HAL_XILINX_GPIO.c
    )
endif()

if(ENABLE_DEMO)
  add_executable(lcd_demo_mock_effects demo/lcd_demo_mock_effects.c)
  target_link_libraries(lcd_demo_mock_effects hd44780)

  add_executable(lcd_demo_mock_format demo/lcd_demo_mock_format.c)
  target_link_libraries(lcd_demo_mock_format hd44780)

  add_executable(lcd_demo_xilinx demo/lcd_demo_xilinx.c)
  target_link_libraries(lcd_demo_xilinx hd44780)
endif()

# Add Unity
add_subdirectory(third_party/unity)

# Add test executable
add_executable(lcd_test tests/lcd_test.c)
target_link_libraries(lcd_test unity)
target_include_directories(lcd_test PRIVATE third_party/unity/src)
