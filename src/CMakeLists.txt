cmake_minimum_required(VERSION 3.13)

include(../pico_sdk_import.cmake)
pico_sdk_init()

file(GLOB FILES *.c *.h)

project(scratch_src)
add_executable(scratch_src scratch.c ${FILES})
# add_library(scratch_src ${FILES})

pico_enable_stdio_uart(scratch_src 1)
pico_enable_stdio_usb(scratch_src 0)

pico_add_extra_outputs(scratch_src)

target_link_libraries(scratch_src pico_stdlib)
target_link_libraries(scratch_src
    hardware_spi
    hardware_i2c
    hardware_gpio
    )
