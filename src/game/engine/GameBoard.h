//
// Created by felix on 06/10/23.
//

#ifndef DOMINATORIX_GAMEBOARD_H
#define DOMINATORIX_GAMEBOARD_H

#include <ostream>
#include <bitset>
#include <vector>
#include <span>

// This class is meant to efficiently store the board representation
class GameBoard {
private:
    // Implement tu use of c++ 23 multispan / mdspan to reshape flat array in row, col TODO
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
    std::vector<std::tuple<char, char, char>> get_board_groups() const;
    bool is_empty() const;
    char cumulative_sum() const;
};


#endif //DOMINATORIX_GAMEBOARD_H
