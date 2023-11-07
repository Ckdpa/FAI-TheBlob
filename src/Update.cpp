//
// Created by felix on 20/10/23.
//

#include "Update.h"


Update::Update(char row, char col, char number_entities, GameTeam& moving_team)
: x_(row), y_(col), number_entities_(number_entities), moving_team_(moving_team){
}

GameTeam Update::get_moving_team() const {
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
