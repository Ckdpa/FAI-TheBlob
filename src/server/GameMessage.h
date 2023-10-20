//
// Created by felix on 16/10/23.
//

#ifndef DOMINATORIX_GAMEMESSAGE_H
#define DOMINATORIX_GAMEMESSAGE_H


#include <string>

class GameMessage {
public:
    enum class MessageType {
        SET,
        HME,
        MAP,
        UPD,
        END,
        BYE,
        UNKNOWN
    };

    GameMessage() = default;
    virtual ~GameMessage() = default;
    virtual void encode() = 0;
    static MessageType parse_message_type(const std::string &bytes);
};
// Héritage ?
class SetMessage : public GameMessage {

};

#endif //DOMINATORIX_GAMEMESSAGE_H
