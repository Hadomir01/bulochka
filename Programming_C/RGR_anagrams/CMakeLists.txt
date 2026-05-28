cmake_minimum_required(VERSION 3.10)
project(AnagramGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(anagram_generator
    src/main.cpp
    src/anagram_utils.cpp
    src/config.cpp
)

target_include_directories(anagram_generator PRIVATE include)

if(WIN32)
    target_compile_definitions(anagram_generator PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()