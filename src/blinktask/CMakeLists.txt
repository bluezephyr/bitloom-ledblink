add_library(blinktask
    blinktask.c
    blinktask.h
    )

target_include_directories(blinktask PRIVATE ${BITLOOM_CORE}/include)
target_include_directories(blinktask PRIVATE ${BITLOOM_CONFIG})

