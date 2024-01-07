//
// Created by felix on 07/11/23.
//

#ifndef DOMINATORIX_MOVMESSAGE_H
#define DOMINATORIX_MOVMESSAGE_H


#include <vector>
#include "GameMessage.h"
#include "game/engine/Move.h"

class MOVMessage : public GameMessage {
public:
    std::string encode() const override;
    MessageType get_message_type() const override;

//    explicit MOVMessage(const char* data);
    explicit MOVMessage(std::vector<Move>& moves);
private:
    std::vector<Move> moves_;

};


#endif //DOMINATORIX_MOVMESSAGE_H
