enable_language(C)
set(CMAKE_C_STANDARD 99)

add_library(compass
    compass.c
    compass.h
    )

target_include_directories(compass PUBLIC .)
target_include_directories(compass PRIVATE ${BITLOOM_CORE}/include)
target_include_directories(compass PRIVATE ${BITLOOM_CONFIG})

