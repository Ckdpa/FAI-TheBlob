//
// Created by felix on 16/10/23.
//

#ifndef DOMINATORIX_CONNECTION_H
#define DOMINATORIX_CONNECTION_H

#include <string>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include "server/messages/GameMessage.h"

// Connect to the server using TCP/IP Socket on a given port and IP adress
class Connection {
/*
public:
    Connection(const std::string& ip, int port);
    ~Connection();
    int connect_socket();
    int close_connection();
    void socket_write(const GameMessage& message);
    bool pending_message();
    GameMessage* read_socket();
private:
    int socket_init(void);
    int socket_quit(void);
    struct sockaddr_in conn_info_{};
    CONN_STATUS status_;
    struct pollfd ufds_[1]{};
    char buff_[1024]{};
*/
public:

    Connection(const std::string& ip, int port);
    ~Connection();
    int close_connection();
    int connect_socket();
    void socket_write(const GameMessage& message);
    bool pending_message();
    int get_total_bytes_read() const;
    int get_total_bytes_used() const;
    std::string consume_nchars(int n_chars);
private:
    bool read_socket(int n_chars);
    void check_overflow(int n_chars);
    int total_bytes_read_ = 0;
    int total_bytes_used_ = 0;
    SOCKET socket_{};
    sockaddr_in conn_info_{};
    enum class CONN_STATUS { DISCONNECTED, CONNECTED, ERROR_STATE };
    CONN_STATUS status_;
    char buff_[1024]{}; // Adjust the buffer size as needed
};



#endif //DOMINATORIX_CONNECTION_H
