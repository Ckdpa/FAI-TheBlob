//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_UPDMESSAGE_H
#define DOMINATORIX_UPDMESSAGE_H


#include <vector>
#include "GameMessage.h"
#include "Move.h"

class UPDMessage : public GameMessage {
public:
    std::string encode() const override;

    UPDMessage(char* data);

    explicit UPDMessage(std::vector<Move>& moves);
private:
    std::vector<Move> moves_;
};


#endif //DOMINATORIX_UPDMESSAGE_H
