//
// Created by felix on 08/10/23.
//

#include <iomanip>
#include <iostream>
#include <tuple>
#include <cmath>
#include "Game.h"
#include <ranges>

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << "Current team:" << (int) game.current_team_ << std::endl;
    os << "Next team:" << static_cast<int>(game.next_team()) << std::endl;
    for (char row = 0; row < game.rows_; row++) {
        for (char col = 0; col < game.columns_; col++) {
            if (game.boards_[HUMAN_BOARD].get(row, col)) {
                os << std::setfill(' ') << std::setw(3) << 0 + game.boards_[HUMAN_BOARD].get(row, col) << 'H';
            } else if (game.boards_[VAMPIRE_BOARD].get(row, col)) {
                os << std::setfill(' ') << std::setw(3) << 0 + game.boards_[VAMPIRE_BOARD].get(row, col) << 'V';
            } else if (game.boards_[WEREWOLF_BOARD].get(row, col)) {
                os << std::setfill(' ') << std::setw(3) << 0 + game.boards_[WEREWOLF_BOARD].get(row, col) << 'W';
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
                 GameBoard(rows, columns),
                 GameBoard(rows, columns),
                 GameBoard(rows, columns)
         }),
         current_team_(team)
{
}

GameTeam Game::next_team() const {
    return static_cast<GameTeam>(1 - static_cast<int>(current_team_));
}

std::vector<std::tuple<char, char, char, std::vector<std::pair<char, char>>>> Game::generate_per_group_possibilities() const {
    auto& home_board = boards_[static_cast<int>(current_team_)];
    auto& enemy_board = boards_[static_cast<int>(next_team())];
    auto& human_board = boards_[HUMAN_BOARD];
//    std::cout << "Teams : curr / next / hum: " << static_cast<int>(current_team_) << static_cast<int>(next_team()) << HUMAN_BOARD << std::endl;
//    std::cout << "Boards" << std::endl << home_board << std::endl << enemy_board << std::endl << human_board << std::endl;
    std::vector<std::tuple<char, char, char, std::vector<std::pair<char, char>>>> group_available_targets; // n_units, row, col, {cell_1, cell2..., cell_n}
    for (char row = 0; row < rows_; row++) {
        for (char col = 0; col < columns_; col++) {
            char units = home_board.get(row, col);
            if (units) {
//                std::cout << "Get: found " << (int) units << " at position " << (int) row << ", " << (int) col << std::endl;
                std::vector<std::pair<char, char>> available_cells;
                // We have units here : Check surrounding cells
                for (int target_row = row - 1; target_row <= row + 1; target_row++) {
                    for (int target_col = col - 1; target_col <= col + 1; target_col++) {
                        // Check if the target cell is in boundaries
                        if (target_row >= 0 && target_row < rows_ && target_col >= 0 && target_col < columns_) {
                            // Do not generate obviously losing moves : cell is occupied and too powerful for the group
                            if (human_board.get(target_row, target_col) > units or
                                enemy_board.get(target_row, target_col) >= std::ceil(1.5 * units)) {
                                continue;
                            }
                            available_cells.emplace_back(target_row, target_col);
                        }
                    }
                }
                group_available_targets.emplace_back(units, row, col, available_cells);
            }
        }
    }
    return group_available_targets;
}

void Game::set_home(char row, char col) {
    if (boards_[WEREWOLF_BOARD].get(row, col)) {
        current_team_ = GameTeam::WEREWOLF;
    }
    else {
        current_team_ = GameTeam::VAMPIRE;
    }
}

void Game::set_humans(const std::vector<std::pair<const char, const char>>& humans_coordinates) {
    for (auto& human_house : humans_coordinates) {
        auto& [y, x] = human_house;
        if (x < 0 or x >= rows_) {
            std::cerr << "Error: trying to set x=" << (int) x << " in board with " << (int) rows_ << "rows" << std::endl;
        }
        if (y < 0 or y >= columns_) {
            std::cerr << "Error: trying to set y=" << (int) y << " in board with " << (int) columns_ << "columns" << std::endl;
        }
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
    if (boards_[(int) next_team()].is_empty()) {
        return 99999.;
    }
    if (boards_[(int) current_team_].is_empty()) {
        return -99999.;
    }
    return 1000 * boards_[(int) current_team_].cumulative_sum() - boards_[(int) next_team()].cumulative_sum();
}

std::vector<std::vector<Move>> Game::generate_legal_moves() const {
    auto moves_per_group = generate_per_group_possibilities();
    std::vector<std::vector<Move>> ret;
    for (const auto& possible_group_move : moves_per_group) {
        // Every loop turn will yield all the possible moves that a group can do.
        // No split for now
        auto [n_units, starting_row, starting_col, possible_destination_cells] = possible_group_move;

        for (auto possible_destination_cell : possible_destination_cells) {
            auto [ending_row, ending_col] = possible_destination_cell; //< Retrieve the coordinates
            // Skip staying still move
            if (starting_col == ending_col and starting_row == ending_row) {
                continue;
            }
            // Create a new move for every cell we can reach (monoblob strategy)
            ret.emplace_back();
            ret.back().emplace_back(starting_row, starting_col, ending_row, ending_col, n_units);
        }
    }
    return ret;
}

Game::Game(const Game &other)
:rows_(other.rows_),
columns_(other.columns_),
boards_(std::array<GameBoard, 3>{other.boards_[0],
                                 other.boards_[1],
                                 other.boards_[2]
}),
current_team_(other.current_team_){
}

Game Game::simulate_move(std::vector<Move> moves) const {
    Game ret =  Game(*this);
    for (const auto& move : moves) {
        char starting_x = move.get_starting_x();
        char starting_y = move.get_starting_y();
        char ending_x = move.get_ending_x();
        char ending_y = move.get_ending_y();
        char number_entities = move.get_number_entities();
        char initial_entities = ret.boards_[(int) ret.current_team_].get(starting_x, starting_y);
        ret.boards_[(int) ret.current_team_].set(starting_x, starting_y, initial_entities - number_entities);

        // Check for humans and update number of moving entities if there are some
        char human_on_target = ret.boards_[HUMAN_BOARD].get(ending_x, ending_y);
        char enemies_on_target = ret.boards_[(int) ret.next_team()].get(ending_x, ending_y);

        if (number_entities > human_on_target) {
            number_entities += human_on_target;
            ret.boards_[HUMAN_BOARD].set(ending_x, ending_y, 0);
        } else {
            // RIP to the entities!
            number_entities = 0;
        }
        if (enemies_on_target >= std::ceil(1.5 * number_entities)) {
            // RIP entities
            number_entities = 0;
        } else if (number_entities >= std::ceil(1.5 * enemies_on_target)) {
            // RIP enemies
            ret.boards_[(int) ret.next_team()].set(ending_x, ending_y, 0);
        } else {
            // Battle simulation ; for now we will consider that this is always a loss for the entities TODO
            number_entities = 0;
            // Decide winning team using random chance
            // Update the values of enemy and entities accordingly to the outcome
        }
        ret.boards_[(int) current_team_].set(ending_x, ending_y, number_entities);
    }
//    ret.update_playing_team();
    return ret;
}

bool Game::is_over() const {
    return boards_[WEREWOLF_BOARD].is_empty() or boards_[VAMPIRE_BOARD].is_empty();
}

void Game::print_boards() const {
    std::cout << "Vampires" << std::endl << boards_[VAMPIRE_BOARD];
    std::cout << "Humans" << std::endl <<  boards_[HUMAN_BOARD];
    std::cout << "Werewolves" << std::endl <<  boards_[WEREWOLF_BOARD];
}

int Game::compute_distance(const std::tuple<char, char, char> &group_a, const std::tuple<char, char, char> &group_b) {
    const auto& [units_a, row_a, col_a] = group_a;
    const auto& [units_b, row_b, col_b] = group_b;
    return std::sqrt((row_a - row_b) * (row_a - row_b) + (col_a - col_b) * (col_a - col_b));
}

void Game::update_playing_team() {
    current_team_ = next_team();
}
