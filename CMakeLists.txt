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
        src/server/MessageHandler.h
        src/server/MessageHandler.cpp
        src/server/messages/NMEMessage.h
        src/server/messages/NMEMessage.cpp
        src/server/messages/GameMessage.h
        src/server/messages/GameMessage.cpp
        src/server/messages/BYEMessage.h
        src/server/messages/BYEMessage.cpp
        src/server/messages/ENDMessage.h
        src/server/messages/ENDMessage.cpp
        src/server/messages/UPDMessage.h
        src/server/messages/UPDMessage.cpp
        src/server/messages/MAPMessage.h
        src/server/messages/MAPMessage.cpp
        src/server/messages/HUMMessage.h
        src/server/messages/HUMMessage.cpp
        src/server/messages/SETMessage.h
        src/server/messages/SETMessage.cpp
        src/server/messages/HMEMessage.h
        src/server/messages/HMEMessage.cpp
        src/server/messages/MOVMessage.h
        src/server/messages/MOVMessage.cpp
        src/Update.h
        src/Update.cpp
        src/GameTeam.h
        src/Move.h
        src/Move.cpp
)

target_link_libraries(Dominatorix ws2_32)

target_compile_options(Dominatorix PRIVATE /W4)