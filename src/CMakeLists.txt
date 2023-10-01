add_library(
            TCPServer_lib
            STATIC)

target_sources(
            TCPServer_lib
            PRIVATE
            TCPServer.cpp
            NetworkUtils.cpp
            )

target_include_directories(
            TCPServer_lib
            PUBLIC
            ./)

add_executable(
            TCPServer
            main.cpp)

target_include_directories(
                TCPServer
                PUBLIC
                ./)
            
target_link_libraries(
            TCPServer
            TCPServer_lib
            pthread)