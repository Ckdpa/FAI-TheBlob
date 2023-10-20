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
        src/server/Connection.h
        src/server/Connection.cpp
        src/server/GameMessage.h
        src/server/GameMessage.cpp
        src/server/BYEMessage.h
        src/server/BYEMessage.cpp
        src/server/ENDMessage.h
        src/server/ENDMessage.cpp
        src/server/UPDMessage.h
        src/server/UPDMessage.cpp
        src/server/HUMMessage.h
        src/server/HUMMessage.cpp
        src/server/SETMessage.h
        src/server/SETMessage.cpp
        src/server/HMEMessage.h
        src/server/HMEMessage.cpp
        src/Move.h
        src/Move.cpp
)
