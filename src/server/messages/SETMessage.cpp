//
// Created by felix on 20/10/23.
//

#include "SETMessage.h"

std::string SETMessage::encode() const {
    return "ERROR"; // We should no send SET messages
}

SETMessage::SETMessage(std::string data)
:rows_(data[0]), columns_(data[1]){
}

char SETMessage::get_rows() const {
    return rows_;
}

char SETMessage::get_columns() const {
    return columns_;
}

GameMessage::MessageType SETMessage::get_message_type() const {
    return GameMessage::MessageType::SET;
}
