//
// Created by felix on 20/10/23.
//

#include "Move.h"

Move::Move(char starting_row, char ending_row, char number_entities, Game::Team moving_team)
:starting_row_(starting_row), ending_row_(ending_row), number_entities_(number_entities), moving_team_(moving_team){
}

Game::Team Move::get_moving_team() const {
    return moving_team_;
}

char Move::get_starting_row() const {
    return starting_row_;
}

char Move::get_ending_row() const {
    return ending_row_;
}

char Move::number_entities() const {
    return number_entities_;
}
