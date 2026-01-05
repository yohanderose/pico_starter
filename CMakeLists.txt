cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
# include(pico_extras_import.cmake)

project(pipod-classic C CXX ASM)
include(CheckLibraryExists)

pico_sdk_init()

add_executable(main
    src/main.c
)

target_link_libraries(main PRIVATE
    pico_stdlib
    pico_cyw43_arch_none
    pico_multicore
    hardware_pwm
    hardware_spi
    hardware_adc
    hardware_pio
    hardware_dma
)

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
pico_add_extra_outputs(main)
