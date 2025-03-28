cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)

# Projektets namn och språk
project(signal_sender C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Ange sökväg till Pico SDK (justera om den ligger någon annanstans)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Kontrollera om SDK finns
if (NOT EXISTS ${PICO_SDK_PATH})
    message(FATAL_ERROR "PICO_SDK_PATH not found! Please make sure pico-sdk is cloned.")
endif()

# Inkludera Pico SDK
pico_sdk_init()

# Lägg till exekverbart mål
add_executable(signal_sender main.cpp)


# Lägg till nödvändiga bibliotek
target_link_libraries(signal_sender 
    pico_stdlib 
    pico_cyw43_arch 
)

# Aktivera standard I/O via UART och USB
pico_enable_stdio_uart(signal_sender 1)
pico_enable_stdio_usb(signal_sender 0)

# Skapa binärfiler för flash
pico_add_extra_outputs(signal_sender)

