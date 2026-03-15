# Задание: Создать библиотеку pipes из read_pipe.c write_pipe.
cmake_minimum_required(VERSION 3.10)
project(pipes)

add_library(pipes STATIC
    read_pipe.c
    write_pipe.c
)

target_include_directories(pipes PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)