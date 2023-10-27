//
// Created by felix on 27/10/23.
//

#ifndef DOMINATORIX_NMEMESSAGE_H
#define DOMINATORIX_NMEMESSAGE_H


#include <string>
#include "GameMessage.h"

class NMEMessage : public GameMessage {
public:
    NMEMessage(std::string name);

    std::string encode() const override;
private:
    const std::string name_;
};


#endif //DOMINATORIX_NMEMESSAGE_H
