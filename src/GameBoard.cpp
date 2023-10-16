//
// Created by felix on 06/10/23.
//

#include "GameBoard.h"


GameBoard::GameBoard(char rows, char columns)
{
    // Type is not correct, this allocates too much space
    board_ = new char[rows * columns];
}

GameBoard::~GameBoard() {
    delete[] board_;
}

std::ostream &operator<<(std::ostream &os, const GameBoard &game) {
    os << "Board is :" << *game.board_ << std::endl;
    return os;
}

char GameBoard::operator[](int c) const {
    return board_[c];
}






