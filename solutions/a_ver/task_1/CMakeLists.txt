cmake_minimum_required(VERSION 2.7)

add_definitions( -DSOURCE_DIR="${CMAKE_SOURCE_DIR}" )

add_executable(reverse_string reverse_string.cpp)
add_executable(reverse_string_kmp reverse_string_kmp.cpp)
add_executable(rational rational.cpp)
add_executable(islands islands.cpp)
