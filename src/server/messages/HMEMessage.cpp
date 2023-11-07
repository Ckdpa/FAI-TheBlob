//
// Created by felix on 20/10/23.
//

#include "HMEMessage.h"

std::string HMEMessage::encode() const {
    return nullptr; // We should not send this message
}

HMEMessage::HMEMessage(const char *data)
:row_(data[0]), col_(data[1]){

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
