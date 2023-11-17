//
// Created by felix on 20/10/23.
//

#include <iostream>
#include <string>
#include "MessageHandler.h"
#include "server/messages/UPDMessage.h"
#include "server/messages/MAPMessage.h"
#include "server/messages/SETMessage.h"
#include "server/messages/HMEMessage.h"
#include "server/messages/HUMMessage.h"
#include "server/messages/BYEMessage.h"
#include "server/messages/ENDMessage.h"
#include "messages/NMEMessage.h"


GameMessage::MessageType MessageHandler::parse_message_type(const std::string &bytes) {
    std::cout << bytes << std::endl;
    if (bytes == "UPD") {
        return GameMessage::MessageType::UPD;
    }
    else if (bytes == "SET") {
        return GameMessage::MessageType::SET;
    }
    else if (bytes == "HME") {
        return GameMessage::MessageType::HME;
    }
    else if (bytes == "MAP") {
        return GameMessage::MessageType::MAP;
    }
    else if (bytes == "END") {
        return GameMessage::MessageType::END;
    }
    else if (bytes == "BYE") {
        return GameMessage::MessageType::BYE;
    }
    else if (bytes == "HUM") {
        return GameMessage::MessageType::HUM;
    }
    else
        throw std::invalid_argument(bytes);
//        return nullptr;
}

MessageHandler::MessageHandler(std::string ip, std::string port)
:game_conn_(ip, stoi(port)){
}

int MessageHandler::connect()
{
    return game_conn_.connect_socket();
}


bool MessageHandler::init_game(std::string name) {
    auto name_msg = NMEMessage(name);
    game_conn_.socket_write(name_msg);
    return true;
}


bool MessageHandler::pending_message() {
    // Check if there already is a message waiting to be processed or if data is ready to be read
    return (game_conn_.get_total_bytes_read() - game_conn_.get_total_bytes_used() >= 3) || game_conn_.pending_message();
}


GameMessage* MessageHandler::get_next_message() {
    // Retrieve header
    std::string header = game_conn_.consume_nchars(3);
    // Interpretation
    auto msg_type = parse_message_type(header);
    switch (msg_type) {
        case GameMessage::MessageType::END:
            return new ENDMessage();
        case GameMessage::MessageType::BYE:
            return new BYEMessage;
        case GameMessage::MessageType::HME:
            return new HMEMessage(game_conn_.consume_nchars(2));
        case GameMessage::MessageType::HUM:
            return new HUMMessage(parse_payload(2));
        case GameMessage::MessageType::SET:
            return new SETMessage(game_conn_.consume_nchars(2));
        case GameMessage::MessageType::UPD:
            return new UPDMessage(parse_payload(5));
        case GameMessage::MessageType::MAP:
            // Same as UPD ; Use UPD directly (lazy)
            return new MAPMessage(parse_payload(5));
        default:
            // Cases are missing, but this is only client side implementation.
            return nullptr;
    }
    return nullptr;
}

void MessageHandler::send_message(GameMessage *message) {
    game_conn_.socket_write(*message);
}


std::string MessageHandler::parse_payload(int chunk_factor) {
    auto payload_size = game_conn_.consume_nchars(1); // Number of chunks
    auto payload_data = game_conn_.consume_nchars(payload_size[0] * chunk_factor); // Retrieve n chunks * size of chunks
    return payload_size + payload_data; // Concatenate
}