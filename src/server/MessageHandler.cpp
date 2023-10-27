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
    auto head = bytes.substr(0, 3);

    if (head == "UPD") {
        return new UPDMessage(data);
    }
    else if (head == "SET") {
        return new SETMessage(data);
    }
    else if (head == "HME") {
        return new HMEMessage(data);
    }
    else if (head == "MAP") {
        return new UPDMessage(data);
    }
    else if (head == "END") {
        return new UPDMessage(data);
    }
    else if (head == "BYE") {
        return new BYEMessage();
    }
    else
        return nullptr;
}
