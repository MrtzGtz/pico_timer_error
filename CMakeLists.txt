# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.21)

# Include build functions from Pico SDK
include(pico-sdk/pico_sdk_init.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(sequencer C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

add_compile_options(-Wall)
add_compile_options(-Werror)

add_executable(pico_timer_error 
    main.c
    second_core.c)

target_link_libraries(pico_timer_error
    pico_stdlib
    pico_multicore)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(pico_timer_error)