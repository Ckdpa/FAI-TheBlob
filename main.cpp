#include <iostream>
#include "GameBoard.h"
#include "Game.h"

int main(int argc, char* argv[]) {
    auto game = Game(3, 3, Game::Team::VAMPIRE);
    std::cout << game;
    return 0;
}