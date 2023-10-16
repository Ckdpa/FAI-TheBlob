cmake_minimum_required(VERSION 3.26)
project(Dominatorix)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(Dominatorix
        src/GameBoard.cpp
        src/GameBoard.h
        main.cpp
        src/Game.h
        src/Game.cpp
        src/Connection.h
        src/Connection.cpp
        src/GameMessage.h
)
