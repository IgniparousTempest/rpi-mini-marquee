cmake_minimum_required(VERSION 3.6)
project(rpi-mini-marquee)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(rpi-mini-marquee ${SOURCE_FILES})

find_library(ArduiPi_OLED_LIB ArduiPi_OLED)

target_link_libraries(rpi-mini-marquee ${ArduiPi_OLED_LIB})