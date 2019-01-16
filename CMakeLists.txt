cmake_minimum_required(VERSION 3.0)
project(jit_db CXX)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include_directories(third_party/asio-master/asio/include)
include_directories(third_party/http-parser-master)
include_directories(third_party/sql-parser/src)

add_subdirectory(third_party)
add_subdirectory(src)
