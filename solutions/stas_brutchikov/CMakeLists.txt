cmake_minimum_required(VERSION 2.8)

project(Craft_Cpp)

if(${CMAKE_COMPILER_IS_GNUCC} MATCHES 1)
add_definitions(
	-std=c++11
)
endif(${CMAKE_COMPILER_IS_GNUCC} MATCHES 1)

add_subdirectory(1.3)
add_subdirectory(1.4)
add_subdirectory(1.5)

