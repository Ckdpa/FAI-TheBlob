//
// Created by felix on 16/10/23.
//

#ifndef DOMINATORIX_CONNECTION_H
#define DOMINATORIX_CONNECTION_H

#include <string>
#include <netinet/in.h>
#include <sys/poll.h>
#include "server/messages/GameMessage.h"

// Connect to the server using TCP/IP Socket on a given port and IP adress
class Connection {

public:

    enum class CONN_STATUS {
        DISCONNECTED=0,
        CONNECTED=1,
        ERROR=2,
    };
    Connection(const std::string& ip, int port);
    ~Connection();
    int connect_socket();
    int close_connection();
    void socket_write(const GameMessage& message);
    bool pending_message();
    GameMessage* read_socket();
private:
    struct sockaddr_in conn_info_{};
    CONN_STATUS status_;
    struct pollfd ufds_[1]{};
    char buff_[1024]{};
};


#endif //DOMINATORIX_CONNECTION_H
