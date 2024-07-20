cmake_minimum_required(VERSION 3.13)

# include(pico_sdk_import.cmake)

project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
# pico_sdk_init()

# add_executable(scratch src/scratch.c)
add_subdirectory(src)

# pico_enable_stdio_uart(scratch 1)
# pico_enable_stdio_usb(scratch 0)

# pico_add_extra_outputs(scratch)

# target_link_libraries(scratch pico_stdlib)
# target_link_libraries(scratch scratch_src)

