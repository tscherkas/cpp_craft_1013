cmake_minimum_required(VERSION 2.7)

add_definitions( -DSOURCE_DIR="${CMAKE_SOURCE_DIR}" )

add_executable(main main.cpp)
add_executable(main_kmp main_kmp.cpp)
