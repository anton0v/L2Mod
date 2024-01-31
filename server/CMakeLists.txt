cmake_minimum_required(VERSION 3.15)

set(SOURCE src/Main.cpp
           src/TCPServerCon.cpp)

set(HEADERS include/TCPServerCon.h)

add_executable(Server ${SOURCE} ${HEADERS})

target_include_directories(Server PUBLIC include/ ./../include )
target_link_libraries(Server PUBLIC wsock32 ws2_32)