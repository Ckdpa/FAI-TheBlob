//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_UPDATE_H
#define DOMINATORIX_UPDATE_H

#include "GameTeam.h"

class Update {
public:
    Update(char row, char col, char human_update, char vampire_update, char werewolve_update);

    char get_x() const;
    char get_y() const;
    char get_human_update() const;
    char get_vampire_update() const;
    char get_werewolve_update() const;
private:
     char x_;
     char y_;
     char human_update_;
     char vampire_update_;
     char werewolve_update_;
};


#endif //DOMINATORIX_UPDATE_H
