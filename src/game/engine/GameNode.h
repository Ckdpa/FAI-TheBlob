//
// Created by Félix on 18/11/2023.
//

#ifndef DOMINATORIX_GAMENODE_H
#define DOMINATORIX_GAMENODE_H


#include <vector>
#include <memory>
#include "Move.h"
#include "Game.h"

class GameNode {
public:
// Alpha beta


private:
    // Moves that lead to this state; undoing them leads to the previous move
    std::vector<Move> applied_moves_;
    // If we are at root, this pointer leads to the associated board.
    Game game_;
    std::vector<std::unique_ptr<GameNode>> reachable_games_;
};


#endif //DOMINATORIX_GAMENODE_H
