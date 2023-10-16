//
// Created by felix on 16/10/23.
//

#include "GameMessage.h"

GameMessage::MessageType GameMessage::parse_message_type(const std::string&
bytes){
    if (bytes == "UPD") {
        return GameMessage::MessageType::UPD;
    }
    else if (bytes == "SET") {
        return GameMessage::MessageType::SET;
    }
    else if (bytes == "HME") {
        return GameMessage::MessageType::HME;
    }
    else if (bytes == "MAP") {
        return GameMessage::MessageType::MAP;
    }
    else if (bytes == "END") {
        return GameMessage::MessageType::END;
    }
    else if (bytes == "BYE") {
        return GameMessage::MessageType::BYE;
    }
    else
        return GameMessage::MessageType::UNKNOWN;
}

