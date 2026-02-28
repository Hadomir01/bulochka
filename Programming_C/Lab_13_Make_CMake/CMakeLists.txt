cmake_minimum_required(VERSION 3.10)
project(my_project)

option(BUILD_SHARED_LIBS "Build shared library (.so/.dll)" ON)

include_directories(include)

set(LIB_SOURCES src/for_main.c)

if(BUILD_SHARED_LIBS)
    add_library(lib SHARED ${LIB_SOURCES})
    message(STATUS "Building SHARED library")
else()
    add_library(lib STATIC ${LIB_SOURCES})
    message(STATUS "Building STATIC library")
endif()

add_executable(res_2 src/main.c)

target_link_libraries(res_2 lib)