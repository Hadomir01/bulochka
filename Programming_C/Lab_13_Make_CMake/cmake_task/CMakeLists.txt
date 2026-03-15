cmake_minimum_required(VERSION 3.10)
project(my_project)

add_subdirectory(background)
add_subdirectory(pipes)

add_executable(res src/main.c)

target_link_libraries(res PUBLIC background)