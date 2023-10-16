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

Connection::Connection(const std::string& ip, int port) {
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
