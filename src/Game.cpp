//
// Created by felix on 08/10/23.
//

#include <iomanip>
#include "Game.h"

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << "Next team:" << static_cast<int>(game.next_team()) << std::endl;
    int cell_idx; // Iterate on the boards
    int entity_count;
    for (auto row = 0; row < game.rows_; row++) {
        for (auto col = 0; col < game.columns_; col++) {
            cell_idx = row * game.columns_ + col;
            if ((entity_count = game.boards_[HUMAN_BOARD].get(cell_idx))) {
                os << std::setfill(' ') << std::setw(3) << entity_count << 'H';
            } else if ((entity_count = game.boards_[VAMPIRE_BOARD].get(cell_idx))) {
                os << std::setfill(' ') << std::setw(3) << entity_count << 'V';
            } else if ((entity_count = game.boards_[WEREWOLF_BOARD].get(cell_idx))) {
                os << std::setfill(' ') << std::setw(3) << entity_count << 'W';
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

std::queue<GameBoard> Game::generate_moves() const {
    const GameBoard current_board = boards_[static_cast<char>(current_team_)];
    // Ideally, we define or inherit goals and each goal generates moves differently
    // For example, for each group of creatures, should we split the group ? How many creatures to split ?
    for (int row = 0; row < rows_; row++) {
        for (int column = 0; column < columns_; column++) {
            auto creature_group = current_board.get(row * columns_ + column);
            if (creature_group) {

            }
        }
    }

    return {};
}

void Game::set_home(int row, int col) {
    current_team_ = static_cast<GameTeam>(
            (boards_[WEREWOLF_BOARD].get(row * columns_ + col) & static_cast<int>(GameTeam::WEREWOLF)) |
            (boards_[VAMPIRE_BOARD].get(row * columns_ + col) & static_cast<int>(GameTeam::VAMPIRE))
            );
}

void Game::set_humans(const std::vector<std::pair<const char, const char>>& humans_coordinates) {
    for (auto human_house : humans_coordinates) {
        auto row = human_house.first;
        auto col = human_house.second;
        boards_[HUMAN_BOARD].set(row * columns_ + col, 0);
    }
}

void Game::update_state(const std::vector<Update>& updates) {
    for (auto update : updates) {
        boards_[static_cast<int>(update.get_moving_team())].set(
                update.get_x() * columns_ + update.get_y(),
                update.number_entities());
    }
}

std::vector<Move> Game::get_next_move(bool monoblob) {
    auto home_board = boards_[static_cast<int>(current_team_)];
    auto enemy_board = boards_[static_cast<int>(next_team())];
    auto human_board = boards_[HUMAN_BOARD];
    // Retrieves the groups
    auto groups = std::vector<std::tuple<int, char, char>>();
    for (int row = 0; row < rows_; row++) {
        for (int col = 0; col < columns_; col++) {
            char units = home_board.get(row * columns_ + col);
            if (units) {
                // We have units here
                groups.emplace_back(units, row, col);
            }
        }
    }
    // Generate the legal moves for each group
    for (auto& group : groups) {
        char row = std::get<1>(group);
        char col = std::get<2>(group);
        if (row == 0) {

        }
    }
    return std::vector<Move>();
}

int Game::static_eval() const {
    return 0;
}
