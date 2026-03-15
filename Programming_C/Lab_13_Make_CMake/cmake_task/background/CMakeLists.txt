# Задание: Создать библиотеку из background.c и слинковать ее с библиотекой pipes
cmake_minimum_required(VERSION 3.10)
project(background)

add_library(background STATIC
    background.c
)

target_include_directories(background PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(background PRIVATE pipes)