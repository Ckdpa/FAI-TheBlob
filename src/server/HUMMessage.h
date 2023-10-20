//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_HUMMESSAGE_H
#define DOMINATORIX_HUMMESSAGE_H


#include "GameMessage.h"

class HUMMessage : public GameMessage {
public:
    const char* encode() const override;

};


#endif //DOMINATORIX_HUMMESSAGE_H
