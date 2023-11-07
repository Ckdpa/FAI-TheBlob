//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_SETMESSAGE_H
#define DOMINATORIX_SETMESSAGE_H


#include "GameMessage.h"

class SETMessage : public GameMessage {
public:
    SETMessage(const char *data);

    std::string encode() const override;
    MessageType get_message_type() const override;

    char get_rows() const;
    char get_columns() const;
private:
    char rows_;
    char columns_;
};


#endif //DOMINATORIX_SETMESSAGE_H
