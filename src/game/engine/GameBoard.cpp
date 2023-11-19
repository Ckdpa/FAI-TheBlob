//
// Created by felix on 06/10/23.
//

#include "GameBoard.h"


GameBoard::GameBoard(char rows, char columns)
:rows_(rows), columns_(columns), board_(rows * columns, 0)
{
}

GameBoard::~GameBoard() = default;

std::ostream &operator<<(std::ostream &os, const GameBoard &game) {
    // TODO update implementation
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







