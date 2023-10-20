//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_BYEMESSAGE_H
#define DOMINATORIX_BYEMESSAGE_H


#include "GameMessage.h"

class BYEMessage : public GameMessage {
public:
    std::string encode() const override;

    BYEMessage() = default;
};


#endif //DOMINATORIX_BYEMESSAGE_H
