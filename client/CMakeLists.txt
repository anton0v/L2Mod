cmake_minimum_required(VERSION 3.15)

set(SOURCE src/Main.cpp
           src/StringHandler.cpp)

set(HEADERS include/StringHandler.h)

add_executable(Client ${SOURCE} ${HEADERS})

target_include_directories(Client PUBLIC include/)