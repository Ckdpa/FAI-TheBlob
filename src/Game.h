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

#include "Update.h"
#include "GameTeam.h"
#include "Move.h"

class Game {
public:
    Game(char rows, char columns, GameTeam team);
    ~Game() = default;
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
    void set_home(char row, char col);
    void set_humans(const std::vector<std::pair<const char, const char>>& humans_coordinates);
    void update_state(const std::vector<Update>& updates);
    std::vector<Move> get_next_move(bool monoblob=true);
    [[nodiscard]] GameTeam next_team() const;
    int static_eval() const;
    [[nodiscard]] std::queue<GameBoard> generate_moves() const; // Signature is not final
private:
    char rows_;
    char columns_;
    std::array<GameBoard, 3> boards_;
    GameTeam current_team_;
};


#endif //DOMINATORIX_GAME_H
