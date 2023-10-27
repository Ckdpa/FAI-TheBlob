//
// Created by felix on 08/10/23.
//

#ifndef DOMINATORIX_GAME_H
#define DOMINATORIX_GAME_H


#include <queue>
#include <array>
#include "GameBoard.h"

#define HUMAN_BOARD 2
#define VAMPIRE_BOARD 1
#define WEREWOLF_BOARD 0

class Game {
public:

    enum class Team {
        WEREWOLF = 0,
        VAMPIRE = 1,
        HUMAN = 2,
    };
    Game(char rows, char columns, Team team);
    ~Game() = default;
    friend std::ostream& operator<<(std::ostream& os, const Game& game);

    void set_home(int row, int col);

    [[nodiscard]] Team next_team() const;

    [[nodiscard]] std::queue<GameBoard> generate_moves() const;
private:
    char rows_;
    char columns_;
    std::array<GameBoard, 3> boards_;
    Team current_team_;
};


#endif //DOMINATORIX_GAME_H
