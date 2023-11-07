//
// Created by felix on 07/11/23.
//

#include <sstream>
#include "MOVMessage.h"

MOVMessage::MOVMessage(std::vector<Move> &moves)
:moves_(moves)
{}

GameMessage::MessageType MOVMessage::get_message_type() const {
    return GameMessage::MessageType::MOV;
}

std::string MOVMessage::encode() const {
    std::stringstream encoded_MOV("MOV");
    encoded_MOV << static_cast<char>(moves_.size());
    for (auto move : moves_) {
        encoded_MOV << move.get_starting_x() << move.get_starting_y(); //  Source coordinates
        encoded_MOV << move.get_number_entities();
        encoded_MOV << move.get_ending_x() << move.get_ending_y(); // Target coordinates
    }
    return encoded_MOV.str();
}
