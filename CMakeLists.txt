cmake_minimum_required(VERSION 3.13)

Include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(seha_utils
    LANGUAGES C CXX ASM
)

pico_sdk_init()

include_directories(src include)

add_executable(seha_utils src/a.c src/main.S include/pico_utils.h)

pico_add_extra_outputs(seha_utils)
target_link_libraries(seha_utils pico_stdlib)

pico_enable_stdio_usb(seha_utils 1)
pico_enable_stdio_uart(seha_utils 0)

