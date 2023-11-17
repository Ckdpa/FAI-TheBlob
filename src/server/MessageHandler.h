//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_MESSAGEHANDLER_H
#define DOMINATORIX_MESSAGEHANDLER_H


#include "server/messages/GameMessage.h"
#include "server/Connection.h"

class MessageHandler {
public:
    MessageHandler(std::string ip, std::string port);

    int connect();
    bool init_game(std::string program_name);
    bool pending_message();
    GameMessage* get_next_message();
    void send_message(GameMessage *message);
private:
    Connection game_conn_;


    GameMessage::MessageType parse_message_type(const std::string &bytes);
    std::string parse_payload(int chunk_factor);
};


#endif //DOMINATORIX_MESSAGEHANDLER_H
