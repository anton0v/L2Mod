cmake_minimum_required(VERSION 3.15)

set(SOURCE src/Main.cpp
           src/TCPServerCon.cpp
           
           ./../src/Connection.cpp
           ./../src/TCPConnection.cpp)

set(HEADERS include/TCPServerCon.h
            
            ./../include/Connection.h
            ./../include/TCPConnection.h)

add_executable(Server ${SOURCE} ${HEADERS})

target_include_directories(Server PUBLIC include/ ./../include )