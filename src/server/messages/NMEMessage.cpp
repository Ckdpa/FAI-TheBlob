//
// Created by felix on 27/10/23.
//

#include "NMEMessage.h"

#include <utility>
#include <sstream>
#include <iostream>

NMEMessage::NMEMessage(std::string name)
:name_(std::move(name)){

}

std::string NMEMessage::encode() const {
    std::stringstream encoded_NME;
    encoded_NME << "NME" << static_cast<char>(name_.size()) << name_;
    return encoded_NME.str();
}

GameMessage::MessageType NMEMessage::get_message_type() const {
    return GameMessage::MessageType::NME;
}
