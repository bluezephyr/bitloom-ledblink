cmake_minimum_required(VERSION 3.12)
project(avr_config C)

set(CMAKE_C_STANDARD 99)

add_library(config
        avr_port_config.c
        port_config.h
        scheduler_config.h)

