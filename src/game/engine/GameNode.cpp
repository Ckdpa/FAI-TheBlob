//
// Created by Félix on 18/11/2023.
//

#include "GameNode.h"

#include <memory>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>

GameNode::GameNode(Game game)
:reachable_games_()
{
    game_ = std::make_unique<Game>(game);
}

std::vector<Move> GameNode::get_next_move(int depth) {
    const auto& legal_moves = game_->generate_legal_moves();
    const auto& ordered_moves = order_moves(legal_moves);
    std::vector<Move> best_moves;
    auto best_value = -9999999.;
    double value;
    for (const auto& legal_move : ordered_moves) {
        // Update the vector of reachable games
        reachable_games_.emplace_back(std::make_unique<GameNode>(GameNode(game_->simulate_move(legal_move, true))));
        value = reachable_games_.back()->alpha_beta(depth - 1, -99999., 99999., false);
        if (value > best_value) {
            best_moves = legal_move;
            best_value = value;
        }
    }
    return best_moves;
}

std::vector<Move> GameNode::get_next_move_2(int depth) {
    const auto& legal_moves = game_->generate_legal_moves();
    const auto& ordered_moves = order_moves(legal_moves);
    std::vector<Move> best_moves;
    int best_value = -99999;
    double value;
    for (const auto& legal_move : ordered_moves) {
        // Update the vector of reachable games
        reachable_games_.emplace_back(std::make_unique<GameNode>(GameNode(game_->simulate_move(legal_move, false))));
        value = reachable_games_.back()->alpha_beta_max(-99999, 99999, depth);
        if (value > best_value) {
            best_moves = legal_move;
            best_value = value;
        }
    }
    return best_moves;
}


// Following wikipedia
int GameNode::alpha_beta(int depth, int alpha, int beta, bool maximizing) {
    if (depth <= 0 or game_->is_over()) {
        return game_->static_eval();
    }
    game_->update_playing_team();
    if (maximizing) {
        int value = -99999; // -inf
        for (const auto& legal_move : game_->generate_legal_moves()) { // for each child of node
//            for (const auto& move : legal_move) {
//                std::cout << "Checking move: " << move << std::endl;
//            }
            reachable_games_.emplace_back(std::make_unique<GameNode>(GameNode(game_->simulate_move(legal_move, false))));
//            std::cout << "Simulated game at depth " << depth << ":" << std::endl << *(reachable_games_.back()->game_) << std::endl;
            value = std::max(value, reachable_games_.back()->alpha_beta(depth - 1, alpha, beta, false));
            alpha = std::max(alpha, value);
            if (value >= beta) {
                // beta cut-off
                break;
            }
        }
        return value;
    } else {
        int value = 99999.;
        for (const auto& legal_move : game_->generate_legal_moves()){
            reachable_games_.emplace_back(std::make_unique<GameNode>(GameNode(game_->simulate_move(legal_move, false))));
            value = std::min(value, reachable_games_.back()->alpha_beta(depth - 1, alpha, beta, true));
            beta = std::min(beta, value);
            if (value <= alpha) {
                // Alpha cut-off
                break;
            }
        }
        return value;
    }
    return 0;
}

int GameNode::alpha_beta_max(int alpha, int beta, int depthleft) {
    int score;
    if (depthleft <= 0 or game_->is_over())
        return game_->static_eval();

    reachable_games_.clear();

    for (const auto& legal_move : game_->generate_legal_moves()){
        reachable_games_.emplace_back(std::make_unique<GameNode>(GameNode(game_->simulate_move(legal_move, true))));
        score = reachable_games_.back()->alpha_beta_min(alpha, beta, depthleft - 1);
        if(score >= beta)
            return beta;   // fail hard beta-cutoff
        if(score > alpha)
            alpha = score; // alpha acts like max in MiniMax
    }
    return alpha;
}

int GameNode::alpha_beta_min(int alpha, int beta, int depthleft) {
    int score;
    if (depthleft == 0 or game_->is_over())
        return -game_->static_eval();

    reachable_games_.clear();

    for (const auto& legal_move : game_->generate_legal_moves()){
        reachable_games_.emplace_back(std::make_unique<GameNode>(GameNode(game_->simulate_move(legal_move, true))));
        score = reachable_games_.back()->alpha_beta_max(alpha, beta, depthleft - 1);
        if(score <= alpha)
            return beta;   // fail hard beta-cutoff
        if (score < beta)
            beta = score; // alpha acts like max in MiniMax
    }
    return beta;
}

std::vector<std::vector<Move>> GameNode::order_moves(const std::vector<std::vector<Move>> &moves) {

    const auto& human_groups = game_->boards_[HUMAN_BOARD].get_board_groups();

    std::vector<int> distances{};
    bool available_resources = false;
    for (const auto& group_move : moves) {
        double move_distance = 0.;
        for (const auto& move : group_move) {
            int tmp = 256 * 256;
            int row_f = (int) move.get_ending_x();
            int col_f = (int) move.get_ending_y();
            int units_f = (int) move.get_number_entities();
//            int n = (int) move.get_number_entities();
            for (const auto& human_group : human_groups) {
                const auto& [units_h, row_h, col_h] = human_group;
                if (units_h < units_f) {
                    tmp = std::min(tmp,
                                   (row_h - row_f) * (row_h - row_f) + (col_h - col_f) * (col_h - col_f));
                    available_resources = true;
                }
            }
            move_distance += tmp;
        }
        distances.emplace_back(move_distance);
    }
    // No humans reachable with that group
    if (!available_resources) {
        std::cout << "No humans available" << std::endl;
        // Do the same as above, but with opponents.
        const auto &enemy_groups = game_->boards_[(int) game_->next_team()].get_board_groups();
        for (const auto& group_move : moves) {
            double move_distance = 0.;
            for (const auto& move : group_move) {
                double tmp = 512.;
                int row_f = (int) move.get_ending_x();
                int col_f = (int) move.get_ending_y();
                int units_f = (int) move.get_number_entities();
//            int n = (int) move.get_number_entities();
                for (const auto& human_group : enemy_groups) {
                    const auto& [units_h, row_h, col_h] = human_group;
                    if (units_h < units_f) {
                        tmp = std::min(tmp,
                                       std::sqrt((row_h - row_f) * (row_h - row_f) + (col_h - col_f) * (col_h - col_f)));
                    }
                }
                move_distance += tmp;
            }
            distances.emplace_back(move_distance);
        }
    }
    std::vector<int> indices(moves.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(),
              [&](int i, int j) -> bool {
                  return distances[i] < distances[j];
              });

    std::vector<std::vector<Move>> ret;
    for (int index : indices) {
        ret.emplace_back(moves[index]);
    }
    return ret;
}

int GameNode::negamax(int depth) {
    if ( depth == 0 ) {
        return game_->static_eval();
    }
    int max = -99999;
    int score;
    const auto& legal_moves = game_->generate_legal_moves();
    const auto& ordered_moves = order_moves(legal_moves);
    std::vector<Move> best_moves;
    double value;
    for (const auto& legal_move : ordered_moves) {
        reachable_games_.emplace_back(std::make_unique<GameNode>(GameNode(game_->simulate_move(legal_move, true))));
        score = reachable_games_.back()->negamax(depth - 1);
        score = -negamax(depth - 1);
        if(score > max)
            max = score;
    }
    return max;
}

std::vector<Move> GameNode::get_next_move_3(int depth) {
    int max = -99999;
    int score;
    const auto& legal_moves = game_->generate_legal_moves();
    const auto& ordered_moves = order_moves(legal_moves);
    std::vector<Move> best_moves;
    double value;
    std::vector<Move> ret;
    for (const auto& legal_move : ordered_moves) {
        reachable_games_.emplace_back(std::make_unique<GameNode>(GameNode(game_->simulate_move(legal_move, true))));
        score = reachable_games_.back()->negamax(depth - 1);
        score = -negamax(depth - 1);
        if(score > max) {
            max = score;
            ret = legal_move;
        }

    }
    return ret;
}
