//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_HMEMESSAGE_H
#define DOMINATORIX_HMEMESSAGE_H


#include "GameMessage.h"

class HMEMessage : public GameMessage {
public:
    const char* encode() const override;

};


#endif //DOMINATORIX_HMEMESSAGE_H
