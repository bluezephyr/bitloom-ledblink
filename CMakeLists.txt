cmake_minimum_required(VERSION 3.12)

project(ledblink C)
set(CMAKE_C_STANDARD 99)

# BITLOOM_CORE must be set to where the bitloom-core repo is located
set(BITLOOM_CORE "${CMAKE_CURRENT_SOURCE_DIR}/bitloom-core")

# BITLOOM_HAL needs to be set in order for the project to build correctly.
# For AVR, this is currently set in the toolchain file.

# BITLOOM_CONFIG should be set to the directory containing the configuration
# for the project's target environment as well as the processor specifics.
set(BITLOOM_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/${CONFIG})

# CUTIL is a library containing common c utilities.  CUTIL needs to be set.
set(CUTIL "${CMAKE_CURRENT_SOURCE_DIR}/cutil")

# Output BitLoom specific folders
message(STATUS "CMAKE SOURCE: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "BITLOOM_HAL: ${BITLOOM_HAL}")
message(STATUS "BITLOOM_CONFIG: ${BITLOOM_CONFIG}")
message(STATUS "CMAKE_CROSSCOMPILING: ${CMAKE_CROSSCOMPILING}")

# Make sure that all required variables have been set
if (NOT BITLOOM_HAL)
    message(FATAL_ERROR "BITLOOM_HAL directory not specified.")
endif(NOT BITLOOM_HAL)

if (NOT CONFIG)
    message(FATAL_ERROR "CONFIG directory not specified.")
endif(NOT CONFIG)

# Use the cross-compile version of add_executable defined in the toolchain
cc_add_executable(ledblink
        src/main.c
        )

# The following directory includes the project specific configurations
# Hence it needs to be available for all targets.
include_directories(${BITLOOM_CONFIG})

cc_target_include_directories(ledblink PRIVATE ${BITLOOM_CORE}/include)
cc_target_include_directories(ledblink PRIVATE src/blinktask)
cc_target_include_directories(ledblink PRIVATE src/ledcontrol)

add_subdirectory(bitloom-core/src/scheduler libs/core/scheduler)
add_subdirectory(bitloom-core/src/uart libs/core/uart)
add_subdirectory(${BITLOOM_HAL}/src/timer libs/hal/timer)
add_subdirectory(${BITLOOM_HAL}/src/pin_digital_io libs/hal/pin_digital_io)
add_subdirectory(${BITLOOM_HAL}/src/uart_hal libs/hal/uart_hal)
add_subdirectory(${BITLOOM_CONFIG}/config libs/config)
add_subdirectory(${CUTIL}/src/bytebuffer libs/bytebuffer)
add_subdirectory(src/blinktask libs/blinktask)
add_subdirectory(src/ledcontrol libs/ledcontrol)

cc_target_link_libraries(ledblink blinktask)
cc_target_link_libraries(ledblink ledcontrol)
cc_target_link_libraries(ledblink scheduler)
cc_target_link_libraries(ledblink uart)
cc_target_link_libraries(ledblink timer)
cc_target_link_libraries(ledblink pin_digital_io)
cc_target_link_libraries(ledblink uart_hal)
cc_target_link_libraries(ledblink config)
cc_target_link_libraries(ledblink bytebuffer)
