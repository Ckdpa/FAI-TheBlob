//
// Created by felix on 07/11/23.
//

#ifndef DOMINATORIX_MOVE_H
#define DOMINATORIX_MOVE_H


class Move {
public:
    Move(char starting_row, char starting_col, char ending_row, char ending_col,  char number_entities);

    char get_starting_x() const;
    char get_starting_y() const;
    char get_ending_x() const;
    char get_ending_y() const;
    char get_number_entities() const;
private:
    char starting_x_;
    char starting_y_;
    char ending_x_;
    char ending_y_;
    char number_entities_;
};


#endif //DOMINATORIX_MOVE_H
