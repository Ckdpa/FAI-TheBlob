//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_UPDATE_H
#define DOMINATORIX_UPDATE_H


#include "Game.h"

class Update {
public:
    Update(char starting_row, char ending_row, char number_entities, Game::Team moving_team);

    Game::Team get_moving_team() const;
    char get_x() const;
    char get_y() const;
    char number_entities() const;
private:
     char x_;
     char y_;
     char number_entities_;
     Game::Team moving_team_;
};


#endif //DOMINATORIX_UPDATE_H
