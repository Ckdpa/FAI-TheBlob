//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_MOVE_H
#define DOMINATORIX_MOVE_H


#include "Game.h"

class Move {
    Move(char starting_row, char ending_row, char number_entities, Game::Team moving_team);

    Game::Team get_moving_team() const;
    char get_starting_row() const;
    char get_ending_row() const;
    char number_entities() const;
private:
     char starting_row_;
     char ending_row_;
     char number_entities_;
     Game::Team moving_team_;
};


#endif //DOMINATORIX_MOVE_H
