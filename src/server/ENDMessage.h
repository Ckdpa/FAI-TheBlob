//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_ENDMESSAGE_H
#define DOMINATORIX_ENDMESSAGE_H


#include "GameMessage.h"

class ENDMessage : public GameMessage {
public:
    std::string encode() const override;

    ENDMessage() = default;
};


#endif //DOMINATORIX_ENDMESSAGE_H
