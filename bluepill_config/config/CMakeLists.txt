add_library(config
        port_config.c)

target_include_directories(config PRIVATE ${BITLOOM_HAL}/../cmsis/cmsis-st/Include)
target_include_directories(config PRIVATE ${BITLOOM_HAL}/../cmsis/cmsis_5/CMSIS/Core/Include)
