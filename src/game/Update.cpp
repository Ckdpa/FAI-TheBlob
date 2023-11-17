//
// Created by felix on 20/10/23.
//

#include "Update.h"


Update::Update(char row, char col, char human_update, char vampire_update, char werewolve_update)
: x_(row), y_(col), human_update_(human_update), vampire_update_(vampire_update), werewolve_update_(werewolve_update){
}

char Update::get_x() const {
    return x_;
}

char Update::get_y() const {
    return y_;
}

char Update::get_human_update() const {
    return human_update_;
}

char Update::get_vampire_update() const {
    return vampire_update_;
}

char Update::get_werewolve_update() const {
    return werewolve_update_;
}