//
// Created by felix on 16/10/23.
//

#ifndef DOMINATORIX_GAMEMESSAGE_H
#define DOMINATORIX_GAMEMESSAGE_H


#include <string>

class GameMessage {
protected:
public:
    GameMessage() = default;
    virtual ~GameMessage() = default;
    /**
     * Translate the internal message in the byte representation to be sent to the server.
     * @return
     */
    virtual std::string encode() const = 0;
};

#endif //DOMINATORIX_GAMEMESSAGE_H
