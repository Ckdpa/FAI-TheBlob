//
// Created by felix on 20/10/23.
//

#include "UPDMessage.h"

#include <utility>
#include <sstream>
#include <array>

std::string UPDMessage::encode() const {
    std::stringstream encoded_UPD("UPD");

    std::array<char, 3> moving_entities{};
    encoded_UPD << static_cast<char>(updates_.size());
    for (auto update : updates_) {
        encoded_UPD << update.get_x() << update.get_y(); // Coordinates
        encoded_UPD << update.get_human_update() << update.get_vampire_update() << update.get_werewolve_update(); // Teams
    }
    return encoded_UPD.str();
}

UPDMessage::UPDMessage(std::string data) {
    for (char i = 1; i < data[0]; i += 5) {
        updates_.emplace_back(
            data[i],
            data[i + 1],
            data[i + 2],
            data[i + 3],
            data[i + 4]);
    }
}

UPDMessage::UPDMessage(std::vector<Update>& updates)
:updates_(std::move(updates)){
}

GameMessage::MessageType UPDMessage::get_message_type() const {
    return GameMessage::MessageType::UPD;
}

std::vector<Update> UPDMessage::get_updates() const {
    return updates_;
}
