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

find_library(CMOCKA_LIB cmocka REQUIRED)

add_executable(test_anagram
    test/test_anagram.cpp
    src/anagram_utils.cpp
    src/config.cpp
)

target_include_directories(test_anagram PRIVATE include)
target_link_libraries(test_anagram PRIVATE ${CMOCKA_LIB})

enable_testing()
add_test(NAME anagram_tests COMMAND test_anagram)