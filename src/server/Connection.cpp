//
// Created by felix on 16/10/23.
//

#include "Connection.h"
#include <stdexcept>
/* Linux headers for socket, system
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/poll.h>
*/
// Windows
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <ws2tcpip.h>
#include <iostream>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include "server/MessageHandler.h"

#define MAX_READING_TRIES 3

/*
Connection::Connection(const std::string& ip, int port) {
    ufds_[0].events = POLLIN;
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
    ufds_[0].fd = socket(AF_INET, SOCK_STREAM, 0);
    if (ufds_[0].fd <= 0) {
        perror("Could not open socket");
    }
    connection_status = connect(ufds_[0].fd, reinterpret_cast<const sockaddr *>(&conn_info_), sizeof(conn_info_));
    if (connection_status != 0) {
        perror("Error connecting to server");
    }
    status_ = CONN_STATUS::CONNECTED;
    return connection_status;
}

Connection::~Connection() {
    close_connection();
}

int Connection::close_connection(){
    auto status = close(ufds_[0].fd);
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
        auto write_status = write(ufds_[0].fd, data.c_str() + written_bytes, strlen(data.c_str()) - written_bytes);
        if (write_status < 0) {
            std::cerr << "Error while writing message";
            status_ = CONN_STATUS::ERROR;
        }
        written_bytes += write_status;
    }
}

bool Connection::pending_message() {
    auto rv = poll(ufds_, 1, -1);
    if (rv == -1) {
        perror("poll"); // error occurred in poll()
    } else if (ufds_[0].revents & POLLIN) // Check for waiting "events"
        {
        return true;
    }
    return false;

}

GameMessage *Connection::read_socket() {
//    size_t total_bytes = 0;
//    size_t read_bytes = read(ufds_.fd, &buff_, 1024);
//    std::cout << read_bytes << "Bytes read" << std::endl;
//    total_bytes += read_bytes;
    auto ret = recv(ufds_[0].fd, buff_, sizeof buff_, 0);
    std::cout << ret << std::endl;
//    read_bytes = read(conn_, &buff_ + total_bytes, 1024 - total_bytes);
    std::cout << "Message reading done" << std::endl;
    return MessageHandler::parse_message_type(std::string(buff_, ret)); // Will this greed through messages ?
}
*/

Connection::Connection(const std::string& ip, unsigned short port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock\n";
        throw std::runtime_error("Winsock initialization failed");
    }

    status_ = CONN_STATUS::DISCONNECTED;
    conn_info_.sin_family = AF_INET;
    
    conn_info_.sin_port = htons(port);
    if (InetPton(AF_INET, ip.c_str(), &conn_info_.sin_addr.s_addr) != 1) {
        std::cerr << "Invalid IP adress" << std::endl;
    }
}

Connection::~Connection() {
    close_connection();
    WSACleanup();
}

int Connection::close_connection() {
    int status = closesocket(socket_);
    status_ = CONN_STATUS::DISCONNECTED;
    if (status == SOCKET_ERROR) {
        std::cerr << "Error closing connection: " << WSAGetLastError() << "\n";
    }
    return status;
}

int Connection::connect_socket() {
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ == INVALID_SOCKET) {
        std::cerr << "Could not open socket: " << WSAGetLastError() << "\n";
        return -1;
    }

    if (connect(socket_, reinterpret_cast<const sockaddr*>(&conn_info_), sizeof(conn_info_)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server: " << WSAGetLastError() << "\n";
        closesocket(socket_);
        return -1;
    }

    status_ = CONN_STATUS::CONNECTED;
    return 0;
}

void Connection::socket_write(const GameMessage& message) {
    std::string data = message.encode();
    if (status_ != CONN_STATUS::CONNECTED) {
        std::cerr << "Socket is not connected, cannot write message\n";
        return;
    }

    int written_bytes = 0;
    while (written_bytes < data.size()) {
        auto write_status = send(socket_, data.c_str() + written_bytes, data.size() - written_bytes, 0);
        if (write_status == SOCKET_ERROR) {
            std::cerr << "Error while writing message: " << WSAGetLastError() << "\n";
            status_ = CONN_STATUS::ERROR_STATE;
            return;
        }
        written_bytes += write_status;
    }
}

bool Connection::pending_message() {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(socket_, &readfds);

    // Use select for checking socket status
    int result = select(0, &readfds, nullptr, nullptr, nullptr);
    if (result == SOCKET_ERROR) {
        std::cerr << "Error in select: " << WSAGetLastError() << "\n";
        status_ = CONN_STATUS::ERROR_STATE;
        return false;
    }

    return (result > 0) && FD_ISSET(socket_, &readfds);
}

int Connection::get_total_bytes_read() const {
    return total_bytes_read_;
}

int Connection::get_total_bytes_used() const {
    return total_bytes_used_;
}

void Connection::check_overflow(int n_chars) {
    // Check for potential overflow
    if (total_bytes_read_ + n_chars > sizeof(buff_)) {
        // Flush the consumed data, not necessary anymore
        memmove(buff_, buff_ + total_bytes_used_, total_bytes_read_ - total_bytes_used_);
        // Update indexes
        total_bytes_read_ =  total_bytes_read_ - total_bytes_used_;
        total_bytes_used_ = 0;
    }
}

bool Connection::read_socket(int n_chars) {
    int read_bytes = 0;
    int n_tries = 0;
    while (read_bytes < n_chars){

        // Check if we reached max number of tries
        if (n_tries > MAX_READING_TRIES) {
            std::cerr << "Reached " << MAX_READING_TRIES << " while trying to read n_chars: " << n_chars << std::endl;
            return false;
        }
        // Check if we can read n_chars
        check_overflow(n_chars);

        // Try to fill the buffer
        auto ret = recv(socket_, buff_ + total_bytes_read_, sizeof(buff_) - total_bytes_read_, 0);
        if (ret == SOCKET_ERROR) {
            std::cerr << "Socket error " << WSAGetLastError() << " while trying to read n_chars: " << n_chars << std::endl; 
            return false;
        }

        // Update indexes
        total_bytes_read_ += ret;
        read_bytes += ret;
        n_tries ++;
        }
    return true;
}

std::string Connection::consume_nchars(int n_chars) {
    // Check if we do not have the data already
    if (get_total_bytes_read() - get_total_bytes_used() < n_chars) {
        // Read n_chars from socket.
        if (!read_socket(n_chars)) {
            throw std::runtime_error("Could not read from socket");
        }
    }
    // Retrieve the data
    std::string ret =  std::string(buff_ + total_bytes_used_, n_chars);
    // Update the new used chars value
    total_bytes_used_ += n_chars;
    return ret;
}