//
// Created by Félix on 18/11/2023.
//

#include "GameNode.h"

#include <memory>
#include <iostream>

GameNode::GameNode(Game game)
:reachable_games_()
{
    game_ = std::make_unique<Game>(game);
}

std::vector<Move> GameNode::get_next_move(int depth) {
    auto legal_moves = game_->generate_legal_moves();
    std::vector<Move> best_moves;
    auto best_value = -9999999.;
    double value;
    for (const auto& legal_move : game_->generate_legal_moves()) {
        // Update the vector of reachable games
        reachable_games_.emplace_back(std::make_unique<GameNode>(GameNode(game_->simulate_move(legal_move))));
        value = reachable_games_.back()->alpha_beta(depth, -99999., 99999., false);
        if (value > best_value) {
            best_moves = legal_move;
            best_value = value;
        }
    }
    return best_moves;
    
}

double
GameNode::alpha_beta(int depth, double alpha, double beta, bool maximizing) {
    if (depth == 0 or game_->is_over()) {
        return game_->static_eval();
    }
    if (maximizing) {
        double value = -99999.;
        for (const auto& legal_move : game_->generate_legal_moves()){
            for (const auto& move : legal_move) {
                std::cout << "Checking move: " << move << std::endl;
            }
            reachable_games_.emplace_back(std::make_unique<GameNode>(GameNode(game_->simulate_move(legal_move))));
            std::cout << "Simulated game at depth " << depth << ":" << std::endl << *(reachable_games_.back()->game_) << std::endl;
            value = std::max(value, reachable_games_.back()->alpha_beta(depth - 1, alpha, beta, false));
            alpha = std::max(alpha, value);
            if (beta <= alpha) {
                // beta cut-off
                break;
            }
        }
        return value;
    } else {
        double value = 99999.;
        for (const auto& legal_move : game_->generate_legal_moves()){
            reachable_games_.emplace_back(std::make_unique<GameNode>(GameNode(game_->simulate_move(legal_move))));
            value = std::min(value, reachable_games_.back()->alpha_beta(depth - 1, alpha, beta, true));
            beta = std::min(alpha, value);
            if (beta <= alpha) {
                // Alpha cut-off
                break;
            }
        }
        return value;
    }
    return 0;
}
