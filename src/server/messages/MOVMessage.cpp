//
// Created by felix on 07/11/23.
//

#include "MOVMessage.h"

MOVMessage::MOVMessage(std::vector<Move> &moves) {

}

GameMessage::MessageType MOVMessage::get_message_type() const {
    return GameMessage::MessageType::MOV;
}

std::string MOVMessage::encode() const {
    return std::string();
}
