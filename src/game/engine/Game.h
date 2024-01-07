//
// Created by felix on 08/10/23.
//

#ifndef DOMINATORIX_GAME_H
#define DOMINATORIX_GAME_H


#include <queue>
#include <array>
#include <set>
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
    Game(const Game& other);

    Game simulate_move(std::vector<Move> moves, bool update) const;

    ~Game() = default;
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
    void print_boards() const;
    void set_home(char row, char col);
    void set_humans(const std::vector<std::pair<const char, const char>>& humans_coordinates);
    void update_state(const std::vector<Update>& updates);
    [[nodiscard]] GameTeam next_team() const;
    int static_eval() const;
    std::vector<std::vector<Move>> generate_legal_moves() const;
    bool is_over() const;
    void update_playing_team();

    GameTeam current_team_;

    static int compute_distance(const std::tuple<char, char, char>& group_a, const std::tuple<char, char, char>& group_b);

    std::array<GameBoard, 3> boards_;

private:
    std::vector<std::tuple<char, char, char, std::vector<std::pair<char, char>>>> generate_per_group_possibilities() const;
    char rows_;
    char columns_;
};


#endif //DOMINATORIX_GAME_H
