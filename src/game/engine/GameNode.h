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
    // Wikipedia
    std::vector<Move> get_next_move(int depth=5);

    // Chess Programming
    std::vector<Move> get_next_move_2(int depth=5);

    // Negamax
    std::vector<Move> get_next_move_3(int depth=5);
private:
    // If we are at root, this pointer leads to the associated board.
    std::unique_ptr<Game> game_;
    std::vector<std::unique_ptr<GameNode>> reachable_games_;
    std::vector<std::vector<Move>> order_moves(const std::vector<std::vector<Move>> &vector);

    // Wikipedia
    int alpha_beta(int depth, int alpha, int beta, bool maximizing);

    // Chess Programming
    int alpha_beta_max(int alpha, int beta, int depthleft);
    int alpha_beta_min(int alpha, int beta, int depthleft);

    // Safe
    int negamax(int depth);
};


#endif //DOMINATORIX_GAMENODE_H
