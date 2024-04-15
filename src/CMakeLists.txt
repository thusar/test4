cmake_minimum_required (VERSION 3.22)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_sources(judge FILES judge.cpp socket.cpp)

target_sources(player FILES player.cpp socket.cpp)

add_executable(judge judge.cpp socket.cpp)

add_executable(player player.cpp socket.cpp)