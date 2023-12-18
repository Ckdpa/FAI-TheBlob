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

    std::vector<Move> get_next_move(int depth=6);
    std::vector<Move> get_next_move_2(int depth=7);
private:
    // If we are at root, this pointer leads to the associated board.
    std::unique_ptr<Game> game_;
    std::vector<std::unique_ptr<GameNode>> reachable_games_;
    std::vector<std::vector<Move>> order_moves(const std::vector<std::vector<Move>> &vector);

    double alpha_beta(int depth, double alpha, double beta, bool maximizing);

    int alpha_beta_max(int alpha, int beta, int depthleft);
    int alpha_beta_min(int alpha, int beta, int depthleft);
};


#endif //DOMINATORIX_GAMENODE_H
