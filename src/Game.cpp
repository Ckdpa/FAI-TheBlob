//
// Created by felix on 08/10/23.
//

#include <iomanip>
#include <iostream>
#include <tuple>
#include "Game.h"

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << "Next team:" << static_cast<int>(game.next_team()) << std::endl;
    for (char row = 0; row < game.rows_; row++) {
        for (char col = 0; col < game.columns_; col++) {
            if (game.boards_[HUMAN_BOARD].get(row, col)) {
                os << std::setfill(' ') << std::setw(3) << game.boards_[HUMAN_BOARD].get(row, col) << 'H';
            } else if (game.boards_[VAMPIRE_BOARD].get(row, col)) {
                os << std::setfill(' ') << std::setw(3) << game.boards_[VAMPIRE_BOARD].get(row, col) << 'V';
            } else if (game.boards_[WEREWOLF_BOARD].get(row, col)) {
                os << std::setfill(' ') << std::setw(3) << game.boards_[WEREWOLF_BOARD].get(row, col) << 'W';
            } else {
                os << std::setfill(' ') << std::setw(4) <<  0;
            }
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}

Game::Game(char rows, char columns, GameTeam team)
        :rows_(rows),
         columns_(columns),
         boards_(std::array<GameBoard, 3>{
                 GameBoard(rows_, columns_),
                 GameBoard(rows_, columns_),
                 GameBoard(rows_, columns_)
         }),
         current_team_(team)
{
}

GameTeam Game::next_team() const {
    return static_cast<GameTeam>(1 - static_cast<int>(current_team_));
}

std::vector<std::vector<Move>> Game::generate_moves() const {
    auto& home_board = boards_[static_cast<int>(current_team_)];
    auto& enemy_board = boards_[static_cast<int>(next_team())];
    auto& human_board = boards_[HUMAN_BOARD];
    // Retrieves the groups
    std::vector<std::vector<Move>> generated_moves;
    auto groups = std::vector<std::tuple<char, char, char>>(); // row, col, unit
    for (char row = 0; row < rows_; row++) {
        for (char col = 0; col < columns_; col++) {
            char units = home_board.get(row, col);
            if (units) {
                // We have units here
                groups.push_back({row, col, units});
            }
        }
    }
    // Generate the legal moves for each group
    for (auto& group : groups) {
        // Add a new vector of moves
        generated_moves.emplace_back();

        // Get the information for each group of entity
        char row = std::get<0>(group);
        char col = std::get<1>(group);
        char entities_number = std::get<2>(group);
        // Check surrounding cells with distance of 1 - Distance not parametrable as the problem only allow movement on 8-connected cells.
        for (char target_row = row - 1; target_row < row + 1; target_row++) {
            for (char target_col = col - 1; target_col < col + 1; target_col++) {
                // We only handle monoblob for now, splitting TODO
                // Check if the move is in boundaries
                if (target_row >= 0 && target_row < rows_ && target_col >= 0 && target_col < columns_) {
                    // Do not generate obviously losing moves : cell is occupied and too powerful for the group
                    if (human_board.get(target_row, target_col) > entities_number or enemy_board.get(target_col, target_row) >= ceil(1.5 * entities_number)) {
                        continue;
                    } 
                    generated_moves.back().emplace_back(row, col, target_row, target_col, entities_number);
                }
            }
        }
    }
    return generated_moves;
}

void Game::set_home(char row, char col) {
    current_team_ = static_cast<GameTeam>(
            (boards_[WEREWOLF_BOARD].get(row, col) & static_cast<int>(GameTeam::WEREWOLF)) |
            (boards_[VAMPIRE_BOARD].get(row, col) & static_cast<int>(GameTeam::VAMPIRE))
            );
}

void Game::set_humans(const std::vector<std::pair<const char, const char>>& humans_coordinates) {
    for (auto& human_house : humans_coordinates) {
        boards_[HUMAN_BOARD].set(human_house.first, human_house.second, 0);
    }
}

void Game::update_state(const std::vector<Update>& updates) {
    for (auto& update : updates) {
        boards_[HUMAN_BOARD].set(update.get_x(), update.get_y(), update.get_human_update());
        boards_[VAMPIRE_BOARD].set(update.get_x(), update.get_y(), update.get_vampire_update());
        boards_[WEREWOLF_BOARD].set(update.get_x(), update.get_y(), update.get_werewolve_update());
    }
}


int Game::static_eval() const {
    return 0;
}
