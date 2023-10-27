//
// Created by felix on 20/10/23.
//

#include <iostream>
#include "MessageHandler.h"
#include "UPDMessage.h"
#include "SETMessage.h"
#include "HMEMessage.h"
#include "BYEMessage.h"
#include "ENDMessage.h"


GameMessage* MessageHandler::parse_message_type(const std::string &bytes) {
    auto data = bytes.c_str() + 3;
    auto head = bytes.substr(0, 3);
    std::cout << head << std::endl << data << std::endl;
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
        return new ENDMessage();
    }
    else if (head == "BYE") {
        return new BYEMessage();
    }
    else
        throw std::invalid_argument(data);
//        return nullptr;
}
