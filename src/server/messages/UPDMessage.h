//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_UPDMESSAGE_H
#define DOMINATORIX_UPDMESSAGE_H


#include <vector>
#include "GameMessage.h"
#include "game/engine/Update.h"

class UPDMessage : public GameMessage {
public:
    std::string encode() const override;
    MessageType get_message_type() const override;

    explicit UPDMessage(std::string data);
    explicit UPDMessage(std::vector<Update>& updates);

    std::vector<Update> get_updates() const;
private:
    std::vector<Update> updates_;
};


#endif //DOMINATORIX_UPDMESSAGE_H
