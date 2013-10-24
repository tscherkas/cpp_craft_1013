cmake_minimum_required(VERSION 2.7)

if(UNIX)

    set( CMAKE_CXX_FLAGS  "-std=c++11 -pedantic -pedantic-errors -W -Wall -Wextra -Wconversion" )
    #set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

endif(UNIX)

add_subdirectory(outdated_deal)
add_subdirectory(small_buffer)
add_subdirectory(binary_data)


