//
// Created by felix on 16/10/23.
//

#ifndef DOMINATORIX_GAMEMESSAGE_H
#define DOMINATORIX_GAMEMESSAGE_H


#include <string>

class GameMessage {
protected:
public:
    enum class MessageType {
    END,
    BYE,
    HME,
    HUM,
    NME,
    SET,
    UPD,
    MAP,
};
    GameMessage() = default;
    virtual ~GameMessage() = default;
    /**
     * Translate the internal message in the byte representation to be sent to the server.
     * @return the encoded message in string format to be written in socket
     */
    virtual std::string encode() const = 0;

    virtual MessageType get_message_type() const = 0;
};

#endif //DOMINATORIX_GAMEMESSAGE_H
