cmake_minimum_required(VERSION 3.10)
project(map_reduce_st C)

set(CMAKE_C_STANDARD 99)

include_directories(include)
add_subdirectory(src)

# Original single-function executable
add_executable(MapReduce main.c)
target_link_libraries(MapReduce PRIVATE map_reduce)
