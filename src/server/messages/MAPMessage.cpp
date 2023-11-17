//
// Created by felix on 20/10/23.
//

#include "MAPMessage.h"

#include <utility>
#include <sstream>
#include <array>

std::string MAPMessage::encode() const {
    std::stringstream encoded_MAP("MAP");

    std::array<char, 3> moving_entities{};
    encoded_MAP << static_cast<char>(updates_.size());
    for (auto update : updates_) {
        encoded_MAP << update.get_x() << update.get_y(); // Coordinates
        encoded_MAP << update.get_human_update() << update.get_vampire_update() << update.get_werewolve_update(); // Teams
    }
    return encoded_MAP.str();
}


MAPMessage::MAPMessage(std::string data) {
    for (char i = 1; i < data[0]; i += 5) {
        updates_.emplace_back(
            data[i],
            data[i + 1],
            data[i + 2],
            data[i + 3],
            data[i + 4]);
    }
}

GameMessage::MessageType MAPMessage::get_message_type() const {
    return GameMessage::MessageType::MAP;
}

std::vector<Update> MAPMessage::get_updates() const {
    return updates_;
}
