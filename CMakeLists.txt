cmake_minimum_required(VERSION 3.0.0)
project(lab7 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

link_directories(lib)

add_subdirectory(lib)
add_subdirectory(bin)