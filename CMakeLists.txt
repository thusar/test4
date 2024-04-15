cmake_minimum_required (VERSION 3.22)

include_directories(./include)

project(Test4 VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#target_sources(judge FILES  ./src/judge.cpp ./src/socket.cpp)

#target_sources(player FILES ./src/player.cpp ./src/socket.cpp)

add_executable(judge ./src/judge.cpp ./src/socket.cpp)

add_executable(player ./src/player.cpp ./src/socket.cpp)