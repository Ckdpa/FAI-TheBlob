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
#include "server/MessageHandler.h"

Connection::Connection(const std::string& ip, int port) {

    ufds_.events = POLLIN;
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
    ufds_.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (ufds_.fd <= 0) {
        perror("Could not open socket");
    }
    connection_status = connect(ufds_.fd, reinterpret_cast<const sockaddr *>(&conn_info_), sizeof(conn_info_));
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
    auto status = close(ufds_.fd);
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
    std::string data = message.encode();
    if (status_ != CONN_STATUS::CONNECTED) {
        std::cerr << "Socket is not connected, cannot write message";
    }
    size_t written_bytes = 0;
    while (written_bytes < strlen(data.c_str())) {
        auto write_status = write(ufds_.fd, data.c_str() + written_bytes, strlen(data.c_str()) - written_bytes);
        if (write_status < 0) {
            std::cerr << "Error while writing message";
            status_ = CONN_STATUS::ERROR;
        }
        written_bytes += write_status;
    }
}

bool Connection::pending_message() {
    auto rv = poll(&ufds_, ufds_.fd, 1000);
    std::cout << "Polling result is: " << rv << std::endl;
    if (rv == -1) {
        perror("poll"); // error occurred in poll()
    } else if (rv == 0) {
        return false;
    } else if (ufds_.events & POLLIN) {
        return true;
    } else {
        std::cerr << "Received message in other mode than POLLIN" << std::endl;
    }
    return false;
}

GameMessage *Connection::read_socket() {
    size_t total_bytes = 0;
//    size_t read_bytes = read(ufds_.fd, &buff_, 1024);
//    std::cout << read_bytes << "Bytes read" << std::endl;
//    total_bytes += read_bytes;
    auto ret = recv(ufds_.fd, buff_, sizeof buff_, 0);
    std::cout << ret << std::endl;
//    read_bytes = read(conn_, &buff_ + total_bytes, 1024 - total_bytes);
    std::cout << "Message reading done" << std::endl;
    return MessageHandler::parse_message_type(std::string(buff_, ret)); // Will this greed through messages ?
}
