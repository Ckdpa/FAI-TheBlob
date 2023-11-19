//
// Created by felix on 06/10/23.
//

#ifndef DOMINATORIX_GAMEBOARD_H
#define DOMINATORIX_GAMEBOARD_H

#include <ostream>
#include <bitset>
#include <vector>

// This class is meant to efficiently store the board representation
class GameBoard {
private:
    std::vector<char> board_;
    char rows_;
    char columns_;
    
    void set(int index, char value);
    char get(int index) const;
public:
    GameBoard(char rows, char columns);
    ~GameBoard();
    friend std::ostream& operator<<(std::ostream& os, const GameBoard& game);
    void set(char row, char column, char value);
    char get(char row, char column) const;
};


#endif //DOMINATORIX_GAMEBOARD_H
