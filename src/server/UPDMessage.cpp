//
// Created by felix on 20/10/23.
//

#include "UPDMessage.h"

#include <utility>
#include <sstream>

std::string UPDMessage::encode() const {
    std::stringstream encoded_UPD("UPD");

    std::array<char, 3> moving_entities{};
    encoded_UPD << static_cast<char>(moves_.size());
    for (auto move : moves_) {
        moving_entities.fill(0);
        moving_entities[static_cast<int>(move.get_moving_team())] = move.number_entities();
        encoded_UPD << move.get_starting_row() << move.get_ending_row(); // Coordinates
        encoded_UPD << moving_entities[static_cast<int>(Game::Team::HUMAN)]; // H
        encoded_UPD << moving_entities[static_cast<int>(Game::Team::VAMPIRE)]; // V
        encoded_UPD << moving_entities[static_cast<int>(Game::Team::WEREWOLF)]; // W
    }
    return encoded_UPD.str();
}

UPDMessage::UPDMessage(const char *data) {
    for (char i = 1; i < data[0]; i += 5) {
        Game::Team moving_team;
        char moving_entities;
        char team = 0;
        while (data[i + team] != 0) {
            team++; // Look for the moving team
        }
        moving_team = Game::Team(data[i + team]);
        moving_entities = data[i+2 + team];
        moves_.emplace_back(
            data[i],
            data[i + 1],
            moving_entities,
            moving_team);
    }
}

UPDMessage::UPDMessage(std::vector<Move>& moves)
:moves_(std::move(moves)){
}

GameMessage::MessageType UPDMessage::get_message_type() const {
    return GameMessage::MessageType::UPD;
}
