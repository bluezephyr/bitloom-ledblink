enable_language(C)
set(CMAKE_C_STANDARD 99)

add_library(uarttask
    uarttask.c
    uarttask.h
    )

target_include_directories(uarttask PRIVATE ${BITLOOM_CORE}/include)
target_include_directories(uarttask PRIVATE ${BITLOOM_CONFIG})
target_include_directories(uarttask PRIVATE ${CMAKE_SOURCE_DIR}/blinktask)

