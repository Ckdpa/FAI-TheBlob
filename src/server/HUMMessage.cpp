//
// Created by felix on 20/10/23.
//

#include "HUMMessage.h"

const char *HUMMessage::encode() const {
    return nullptr; // We do not send encode messages
}

HUMMessage::HUMMessage(const char *data) {
    for (auto i = 0; data[i] != 0; i+= 2) {
        humans_coordinates_.emplace_back(data[i], data[i + 1]);
    }
}

std::vector<std::pair<const int, const int>> HUMMessage::get_human_coordinates_() const {
    return humans_coordinates_;
}
