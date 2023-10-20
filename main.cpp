#include <iostream>
#include "GameBoard.h"
#include "Game.h"
#include "server/Connection.h"

int main(int argc, char* argv[]) {
    auto connection = Connection("127.0.0.1", 5555);
    if (connection.connect_socket() < 0) {
        return -1;
    }
    auto game = Game(3, 3, Game::Team::VAMPIRE);
    std::cout << game;
    return 0;
}