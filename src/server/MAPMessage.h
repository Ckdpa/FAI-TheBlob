//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_MAPMESSAGE_H
#define DOMINATORIX_MAPMESSAGE_H


#include "GameMessage.h"

class MAPMessage : public GameMessage {
public:
    const char* encode() const override;

};


#endif //DOMINATORIX_MAPMESSAGE_H
