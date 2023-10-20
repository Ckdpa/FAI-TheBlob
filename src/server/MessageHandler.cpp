//
// Created by felix on 20/10/23.
//

#include "MessageHandler.h"
#include "UPDMessage.h"
#include "SETMessage.h"
#include "HMEMessage.h"
#include "BYEMessage.h"


GameMessage* MessageHandler::parse_message_type(const std::string &bytes) {
    auto data = bytes.c_str() + 3;
    if (bytes == "UPD") {
        return new UPDMessage(data);
    }
    else if (bytes == "SET") {
        return new SETMessage(data);
    }
    else if (bytes == "HME") {
        return new HMEMessage(data);
    }
    else if (bytes == "MAP") {
        return new UPDMessage(data);
    }
    else if (bytes == "END") {
        return new UPDMessage(data);
    }
    else if (bytes == "BYE") {
        return new BYEMessage();
    }
    else
        return nullptr;
}
