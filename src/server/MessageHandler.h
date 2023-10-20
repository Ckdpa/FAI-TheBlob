//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_MESSAGEHANDLER_H
#define DOMINATORIX_MESSAGEHANDLER_H


#include "GameMessage.h"

class MessageHandler {
public:
    static GameMessage* parse_message_type(const std::string &bytes);

};


#endif //DOMINATORIX_MESSAGEHANDLER_H
