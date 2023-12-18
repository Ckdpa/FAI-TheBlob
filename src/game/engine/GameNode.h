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
    explicit GameNode(Game game);

    std::vector<Move> get_next_move(int depth=3);
private:
    // If we are at root, this pointer leads to the associated board.
    std::unique_ptr<Game> game_;
    std::vector<std::unique_ptr<GameNode>> reachable_games_;

    double alpha_beta(int depth, double alpha, double beta, bool maximizing);
};


#endif //DOMINATORIX_GAMENODE_H
