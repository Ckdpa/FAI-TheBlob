//
// Created by felix on 16/10/23.
//

#include "Connection.h"
#include <stdexcept>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <sys/poll.h>

Connection::Connection(const std::string& ip, int port) {

    ufds_.events = POLLIN;
    conn_ = 0;
    status_ = CONN_STATUS::DISCONNECTED;
    conn_info_.sin_family = AF_INET;
    conn_info_.sin_port = htons(port);
    auto status = inet_pton(AF_INET, ip.c_str(), &conn_info_.sin_addr);
    if (status < 0) {
        perror("Conversion failed");
        throw std::invalid_argument("Server configuration is not correct");
    }
}

int Connection::connect_socket() {

    int connection_status;
    conn_ = socket(AF_INET, SOCK_STREAM, 0);
    if (conn_ <= 0) {
        perror("Could not open socket");
    }
    connection_status = connect(conn_, reinterpret_cast<const sockaddr *>(&conn_info_), sizeof(conn_info_));
    if (connection_status != 0) {
        std::cout << errno << std::endl;
        perror("Error connecting to server");
    }
    status_ = CONN_STATUS::CONNECTED;
    return connection_status;
}

Connection::~Connection() {
    close_connection();
}

int Connection::close_connection() const {
    auto status = close(conn_);
    if (status < 0) {
        perror("Error closing connection");
    }
    return status;
}

std::ostream &operator<<(std::ostream &os, const GameMessage &game) {
    os << game.encode();
    return os;
}

void Connection::socket_write(const GameMessage &message) {
    const char* data = message.encode().c_str();
    if (status_ != CONN_STATUS::CONNECTED) {
        std::cerr << "Socket is not connected, cannot write message";
    }
    size_t written_bytes = 0;
    while (written_bytes < strlen(data)) {
        auto write_status = write(conn_, data + written_bytes, strlen(data) - written_bytes);
        if (write_status < 0) {
            std::cerr << "Error while writing message";
            status_ = CONN_STATUS::ERROR;
        }
        written_bytes += write_status;
    }
}

bool Connection::pending_message() {
    auto rv = poll(&ufds_, conn_, 100);
    if (rv == -1) {
        perror("poll"); // error occurred in poll()
    } else if (rv == 0) {
        return false;
    } else if (ufds_.revents & POLLIN) {
        return true;
    } else {
        std::cerr << "Received message in other mode than POLLIN" << std::endl;
    }
}
