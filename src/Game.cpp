//
// Created by felix on 08/10/23.
//

#include "Game.h"

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << "Game is of size "<< game.rows_ << " rows, " << game.columns_ << " columns\n";
    os << "Human board is:" << game.boards_[HUMAN_BOARD] << std::endl;
    os << "Werewolves board is:" << game.boards_[WEREWOLF_BOARD] << std::endl;
    os << "Vampire board is:" << game.boards_[VAMPIRE_BOARD] << std::endl;
    os << "Current playing team:" << static_cast<int>(game.current_team_) << std::endl;
    os << "Next team:" << static_cast<int>(game.next_team()) << std::endl;
    return os;
}

Game::Game(char rows, char columns, Team team)
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

Game::Team Game::next_team() const {
    return static_cast<Game::Team>(1 - static_cast<int>(current_team_));
}

std::queue<GameBoard> Game::generate_moves() const {
    const GameBoard current_board = boards_[static_cast<char>(current_team_)];
    // Ideally, we define or inherit goals and each goal generates moves differently
    // For example, for each group of creatures, should we split the group ? How many creatures to split ?
    for (int row = 0; row < rows_; row++) {
        for (int column = 0; column < columns_; column++) {
            auto creature_group = current_board[row * columns_ + column];
            if (creature_group) {

            }
        }
    }

    return {};
}