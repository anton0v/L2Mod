cmake_minimum_required(VERSION 3.15)

IF (UNIX)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
ENDIF()

set(SOURCE src/Main.cpp
           src/StringHandler.cpp
           src/Summator.cpp
           src/TCPConnection.cpp)

set(HEADERS include/StringHandler.h
            include/Summator.h
            include/TCPConnection.h)

add_executable(Client ${SOURCE} ${HEADERS})

target_include_directories(Client PRIVATE include/)

IF (WIN32)
    target_link_libraries(Client PRIVATE wsock32 ws2_32)
ELSE()
    target_link_libraries(Client PRIVATE Threads::Threads)
ENDIF()
