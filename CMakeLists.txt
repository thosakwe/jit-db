cmake_minimum_required(VERSION 3.0)
project(jit_db CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(lib/sql-parser/src)

add_subdirectory(lib)
add_subdirectory(src)
