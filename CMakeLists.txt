cmake_minimum_required(VERSION 3.10)
project(map_reduce_st C)

set(CMAKE_C_STANDARD 99)

include_directories(include)
add_subdirectory(src)
add_executable(map_reduce_st main.c)
target_link_libraries(map_reduce_st PRIVATE map_reduce)
