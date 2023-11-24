//
// Created by felix on 20/10/23.
//

#include "BYEMessage.h"

std::string BYEMessage::encode() const {
    return "ERROR";
}

GameMessage::MessageType BYEMessage::get_message_type() const {
    return GameMessage::MessageType::BYE;
}

