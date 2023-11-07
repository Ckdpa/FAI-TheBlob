//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_UPDMESSAGE_H
#define DOMINATORIX_UPDMESSAGE_H


#include <vector>
#include "GameMessage.h"
#include "Update.h"

class UPDMessage : public GameMessage {
public:
    std::string encode() const override;
    MessageType get_message_type() const override;

    explicit UPDMessage(const char* data);
    explicit UPDMessage(std::vector<Update>& moves);

    std::vector<Update> get_updates() const;
private:
    std::vector<Update> moves_;
};


#endif //DOMINATORIX_UPDMESSAGE_H
