add_executable(jitdb_daemon
        main.cpp
        database/Environment.cpp database/Environment.h
        database/Database.cpp database/Database.h
        database/Schema.cpp database/Schema.h
        database/Table.cpp database/Table.h
        database/Type.cpp database/Type.h
        frontend/Options.h frontend/Options.cpp
        server/Server.h server/Server.cpp database/Table.cpp compiler/Compiler.cpp compiler/Compiler.h)

find_package(Readline)
target_include_directories(jitdb_daemon PUBLIC ${Readline_INCLUDE_DIR})
target_link_libraries(jitdb_daemon hsql ${Readline_LIBRARY})
set_target_properties(jitdb_daemon PROPERTIES OUTPUT_NAME "jitdb")

install(TARGETS jitdb_daemon
        ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/lib
        RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)