//
// Created by felix on 20/10/23.
//

#include "ENDMessage.h"

std::string ENDMessage::encode() const {
    return "ERROR";
}

GameMessage::MessageType ENDMessage::get_message_type() const {
    return GameMessage::MessageType::END;
}
