//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_HMEMESSAGE_H
#define DOMINATORIX_HMEMESSAGE_H


#include "GameMessage.h"

class HMEMessage : public GameMessage {
public:
    const char* encode() const override;

    explicit HMEMessage(const char* data);

    char get_starting_row() const;
    char get_starting_col() const;
private:
    char row_;
    char col_;
};


#endif //DOMINATORIX_HMEMESSAGE_H
