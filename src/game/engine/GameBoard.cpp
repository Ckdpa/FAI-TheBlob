//
// Created by felix on 06/10/23.
//

#include <iostream>
#include "GameBoard.h"


GameBoard::GameBoard(char rows, char columns)
:rows_(rows), columns_(columns), board_(rows * columns, 0)
{
}

GameBoard::~GameBoard() = default;

std::ostream &operator<<(std::ostream &os, const GameBoard &game) {
    for (auto i = 0; i < game.rows_; i++) {
        for (auto j = 0; j < game.columns_; j++) {
            os << (int) game.get(i, j);
        }
        os << std::endl;
    }
    return os;
}

char GameBoard::get(int index) const {
    return board_[index];
}

void GameBoard::set(int index, char value) {
    board_[index] = value;
}


char GameBoard::get(char row, char column) const {
    return get(row * columns_ + column);
}

void GameBoard::set(char row, char column, char value) {
    set(row * columns_ + column, value);
}

bool GameBoard::is_empty() const {
    return board_ == std::vector<char>(rows_ * columns_, 0);
}

char GameBoard::cumulative_sum() const {
    char ret = 0;
    for (const auto& element : board_) {
        ret += element;
    }
    return ret;
}

std::vector<std::tuple<char, char, char>> GameBoard::get_board_groups() const {
    std::vector<std::tuple<char, char, char>> ret;
    char units;
    for (int row = 0; row < rows_; row++) {
        for (int col = 0; col < columns_; col++) {
            if ((units = get(row, col)) > 0) {
                ret.emplace_back(units, row, col);
            }
        }
    }
    return ret;
}







