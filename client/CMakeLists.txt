cmake_minimum_required(VERSION 3.15)

set(SOURCE src/Main.cpp
           src/StringHandler.cpp
           src/Summator.cpp
           src/TCPConnection.cpp)

set(HEADERS include/StringHandler.h
            include/Summator.h
            include/TCPConnection.h)

add_executable(Client ${SOURCE} ${HEADERS})

target_include_directories(Client PUBLIC include/ ./../include )
target_link_libraries(Client PUBLIC wsock32 ws2_32)