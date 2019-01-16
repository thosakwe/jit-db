add_executable(pubbyd
        ../third_party/http-parser-master/http_parser.c
        main.cpp
        frontend/options.h frontend/options.cc
        database/environment.cc database/environment.h frontend/server.cc frontend/server.h)

find_path(LIBJIT_INCLUDE_DIR jit/jit.h)
find_library(LIBJIT jit)
find_package(Readline)
target_include_directories(pubbyd PUBLIC ${LIBJIT_INCLUDE_DIR} ${Readline_INCLUDE_DIR})
target_link_libraries(pubbyd hsql ${LIBJIT} ${Readline_LIBRARY})

install(TARGETS pubbyd
        ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/lib
        RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)