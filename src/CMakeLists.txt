add_library(jitdb
        frontend/Options.cpp server/Server.cpp database/Database.cpp)

add_executable(jitdb_daemon main.cpp)
find_package(Readline)
target_include_directories(jitdb_daemon PUBLIC ${Readline_INCLUDE_DIR})
target_link_libraries(jitdb_daemon jitdb hsql ${Readline_LIBRARY})
set_target_properties(jitdb_daemon PROPERTIES OUTPUT_NAME "jitdb")

install(TARGETS jitdb jitdb_daemon
        ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/lib
        RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)