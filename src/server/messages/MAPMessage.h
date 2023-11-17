//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_MAPMESSAGE_H
#define DOMINATORIX_MAPMESSAGE_H


#include <vector>
#include "GameMessage.h"
#include "Update.h"

class MAPMessage : public GameMessage {
public:

    std::string encode() const override;

    MessageType get_message_type() const override;

    explicit MAPMessage(std::string data);

    std::vector<Update> get_updates() const;
private:
    std::vector<Update> updates_;
};


#endif //DOMINATORIX_MAPMESSAGE_H
