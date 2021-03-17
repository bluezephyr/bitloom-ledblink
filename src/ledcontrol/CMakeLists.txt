add_library(ledcontrol
        ledcontrol.c
    )

target_include_directories(ledcontrol PRIVATE ${BITLOOM_CORE}/include)
target_include_directories(ledcontrol PRIVATE ${BITLOOM_CONFIG})
target_include_directories(ledcontrol PRIVATE ${CMAKE_SOURCE_DIR}/src/blinktask)
