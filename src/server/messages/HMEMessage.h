//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_HMEMESSAGE_H
#define DOMINATORIX_HMEMESSAGE_H


#include "GameMessage.h"

class HMEMessage : public GameMessage {
public:
    std::string encode() const override;
    MessageType get_message_type() const override;

    explicit HMEMessage(std::string data);

    char get_starting_row() const;
    char get_starting_col() const;
private:
    char row_;
    char col_;
};


#endif //DOMINATORIX_HMEMESSAGE_H
