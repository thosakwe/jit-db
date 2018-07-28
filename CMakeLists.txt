cmake_minimum_required(VERSION 3.0)
project(jit_db CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(third_party/sql-parser/src)

add_subdirectory(third_party)
add_subdirectory(src)
