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
    std::stringstream encoded_MOV;
    encoded_MOV << "MOV";
    encoded_MOV << static_cast<char>(moves_.size());
    for (auto move : moves_) {
        encoded_MOV << move.get_starting_y() << move.get_starting_x(); //  Source coordinates
        encoded_MOV << move.get_number_entities();
        encoded_MOV << move.get_ending_y() << move.get_ending_x(); // Target coordinates
    }
//    encoded_MOV << '\u0004' << '\u0003' << '\u0002' << '\u0003' << '\u0002';
    return encoded_MOV.str();
}
