cmake_minimum_required(VERSION 3.15)

set(SOURCE src/Main.cpp
           src/TCPServerCon.cpp
           ../src/TCPConnection.cpp)

set(HEADERS include/TCPServerCon.h

            ../include/TCPConnection.h)

add_executable(Server ${SOURCE} ${HEADERS})

target_include_directories(Server PRIVATE include/ ../include)

IF (WIN32)
    target_link_libraries(Server PRIVATE wsock32 ws2_32)
ENDIF()
