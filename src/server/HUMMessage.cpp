//
// Created by felix on 20/10/23.
//

#include "HUMMessage.h"

std::string HUMMessage::encode() const {
    return nullptr; // We do not send encode messages
}

HUMMessage::HUMMessage(const char *data) {
    for (auto i = 1; i < data[0]; i+= 2) {
        humans_coordinates_.emplace_back(data[i], data[i + 1]);
    }
}

std::vector<std::pair<const char, const char>> HUMMessage::get_human_coordinates_() const {
    return humans_coordinates_;
}

GameMessage::MessageType HUMMessage::get_message_type() const {
    return GameMessage::MessageType::HUM;
}
