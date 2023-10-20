//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_SETMESSAGE_H
#define DOMINATORIX_SETMESSAGE_H


#include "GameMessage.h"

class SETMessage : public GameMessage {
public:
    const char* encode() const override;

};


#endif //DOMINATORIX_SETMESSAGE_H
