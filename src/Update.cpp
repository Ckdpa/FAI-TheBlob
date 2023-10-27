//
// Created by felix on 20/10/23.
//

#include "Update.h"

Update::Update(char starting_row, char ending_row, char number_entities, Game::Team moving_team)
: x_(starting_row), y_(ending_row), number_entities_(number_entities), moving_team_(moving_team){
}

Game::Team Update::get_moving_team() const {
    return moving_team_;
}

char Update::get_x() const {
    return x_;
}

char Update::get_y() const {
    return y_;
}

char Update::number_entities() const {
    return number_entities_;
}
