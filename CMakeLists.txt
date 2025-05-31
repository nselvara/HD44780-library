cmake_minimum_required(VERSION 3.14)
project(HD44780-Library C)

set(CMAKE_C_STANDARD 99)

# Optional: default to Debug build
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

enable_testing()

option(HD44780_USE_HAL_SIM    "Use Simulation HAL" OFF)
option(HD44780_USE_HAL_XILINX "Use Xilinx GPIO HAL" OFF)
option(HD44780_USE_HAL_MOCK   "Use Mock HAL" OFF)
option(HD44780_USE_HAL_STUB   "Use Stub HAL" OFF)

# ---- Enforce only one HAL backend is active ----
set(hal_count 0)

if(HD44780_USE_HAL_SIM)
  math(EXPR hal_count "${hal_count} + 1")
endif()
if(HD44780_USE_HAL_XILINX)
  math(EXPR hal_count "${hal_count} + 1")
endif()
if(HD44780_USE_HAL_MOCK)
  math(EXPR hal_count "${hal_count} + 1")
endif()
if(HD44780_USE_HAL_STUB)
  math(EXPR hal_count "${hal_count} + 1")
endif()

if(hal_count GREATER 1)
  message(FATAL_ERROR "Only one HD44780 HAL backend may be enabled at a time.")
elseif(hal_count EQUAL 0)
  message(FATAL_ERROR "You must enable exactly one HD44780 HAL backend.")
endif()

# Add subdirectories
add_subdirectory(src)
add_subdirectory(hal)
add_subdirectory(demo)
add_subdirectory(tests)
add_subdirectory(third_party/unity)

# ----------- Platform Defines -----------
if(WIN32)
  add_definitions(-DWIN32_LEAN_AND_MEAN)
endif()

if(UNIX)
  add_definitions(-DUNIX)
endif()

if(HD44780_USE_HAL_XILINX AND WIN32)
  # Add mock Xilinx headers for Windows development
  include_directories(${CMAKE_SOURCE_DIR}/hal/mock_xilinx_includes)
endif()
