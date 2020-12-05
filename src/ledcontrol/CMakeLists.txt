enable_language(C)
set(CMAKE_C_STANDARD 99)

add_library(ledcontrol
        ledcontrol.c
    )

target_include_directories(ledcontrol PUBLIC .)
target_include_directories(ledcontrol PRIVATE ${BITLOOM_CORE}/include)
target_include_directories(ledcontrol PRIVATE ${BITLOOM_CONFIG})
target_include_directories(ledcontrol PRIVATE ${CMAKE_SOURCE_DIR}/src/blinktask)
