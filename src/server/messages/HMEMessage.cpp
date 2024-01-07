//
// Created by felix on 20/10/23.
//

#include "HMEMessage.h"

std::string HMEMessage::encode() const {
    return "ERROR"; // We should not send this message
}

HMEMessage::HMEMessage(std::string data)
:col_(data[0]), row_(data[1]){

}

char HMEMessage::get_starting_row() const {
    return row_;
}

char HMEMessage::get_starting_col() const {
    return col_;
}

GameMessage::MessageType HMEMessage::get_message_type() const {
    return GameMessage::MessageType::HME;
}
