//
// Created by felix on 07/11/23.
//

#include "Move.h"

Move::Move(char starting_row, char starting_col, char ending_row, char ending_col, char number_entities)
:starting_x_(starting_row), starting_y_(starting_col), ending_x_(ending_row), ending_y_(ending_col), number_entities_(number_entities){
}

char Move::get_starting_x() const {
    return starting_x_;
}

char Move::get_starting_y() const {
    return starting_y_;
}

char Move::get_ending_x() const {
    return ending_x_;
}

char Move::get_ending_y() const {
    return ending_y_;
}

char Move::get_number_entities() const {
    return number_entities_;
}

std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << "x_i: " << (int) move.starting_x_
    << ", y_i: " << (int) move.starting_y_
    << ", x_f: " << (int) move.ending_x_
    << ", y_f: " << (int) move.ending_y_
    << ", n: " << (int) move.number_entities_;
    return os;
}
