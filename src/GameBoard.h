//
// Created by felix on 06/10/23.
//

#ifndef DOMINATORIX_GAMEBOARD_H
#define DOMINATORIX_GAMEBOARD_H

#include <ostream>
#include <bitset>

// This class is meant to efficiently store the board representation
class GameBoard {
private:
    char* board_;
    int rows_;
    int columns_;
    
    void set(int index, char value);
    char get(int index) const;
public:
    GameBoard(char rows, char columns);
    ~GameBoard();
    friend std::ostream& operator<<(std::ostream& os, const GameBoard& game);
    void set(int row, int column, char value);
    char get(int row, int column) const;
};


#endif //DOMINATORIX_GAMEBOARD_H
