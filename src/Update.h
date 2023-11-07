//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_UPDATE_H
#define DOMINATORIX_UPDATE_H

#include "GameTeam.h"

class Update {
public:
    Update(char starting_row, char ending_row, char number_entities, GameTeam& moving_team);

    GameTeam get_moving_team() const;
    char get_x() const;
    char get_y() const;
    char number_entities() const;
private:
     char x_;
     char y_;
     char number_entities_;
     GameTeam moving_team_;
};


#endif //DOMINATORIX_UPDATE_H
