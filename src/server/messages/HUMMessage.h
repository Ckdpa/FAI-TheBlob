//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_HUMMESSAGE_H
#define DOMINATORIX_HUMMESSAGE_H


#include <vector>
#include "GameMessage.h"

class HUMMessage : public GameMessage {
public:
    std::string encode() const override;
    MessageType get_message_type() const override;

    explicit HUMMessage(std::string data);

    std::vector<std::pair<const char, const char>> get_human_coordinates_() const;
private:
    std::vector<std::pair<const char, const char>> humans_coordinates_;
};


#endif //DOMINATORIX_HUMMESSAGE_H
