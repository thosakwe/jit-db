add_library(jitdb
        frontend/Options.cpp)

add_executable(jitdb_daemon main.cpp)
target_link_libraries(jitdb_daemon jitdb hsql)
set_target_properties(jitdb_daemon PROPERTIES OUTPUT_NAME "jitdb")

install(TARGETS jitdb jitdb_daemon
        ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/lib
        RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)