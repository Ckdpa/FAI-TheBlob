//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_UPDMESSAGE_H
#define DOMINATORIX_UPDMESSAGE_H


#include "GameMessage.h"

class UPDMessage : public GameMessage {
public:
    const char* encode() const override;

};


#endif //DOMINATORIX_UPDMESSAGE_H
