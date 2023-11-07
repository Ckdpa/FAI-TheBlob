#include <iostream>
#include <unistd.h>
#include "Game.h"
#include "server/Connection.h"
#include "server/messages/NMEMessage.h"
#include "server/messages/HMEMessage.h"
#include "server/messages/HUMMessage.h"
#include "server/messages/SETMessage.h"
#include "server/messages/UPDMessage.h"

bool init_game(Connection conn, const char* name) {
    GameMessage *name_msg = new NMEMessage(name);
    conn.socket_write(*name_msg);
    delete name_msg;
    return true;
}

int main(int argc, char* argv[]) {
    auto connection = Connection("localhost", 5555);
    if (connection.connect_socket() < 0) {
        return -1;
    }
    init_game(connection, "Dominatorix");
    // Initiate game
    bool is_running = true;
    Game* game = nullptr;
    while (is_running) {
        if (not connection.pending_message()) {
            sleep(1);
            continue;
        }
        GameMessage* message = connection.read_socket();
        switch (message->get_message_type()) {
            case GameMessage::MessageType::END:
                delete game;
                game = nullptr;
                // Prepare for next game
                init_game(connection, "Dominatorix");
                break;
            case GameMessage::MessageType::BYE:
                delete game;
                game = nullptr;
                is_running = false;
                break;
            case GameMessage::MessageType::HME:
                game->set_home(dynamic_cast<HMEMessage*>(message)->get_starting_row(),
                               dynamic_cast<HMEMessage*>(message)->get_starting_col());
                break;
            case GameMessage::MessageType::HUM:
                game->set_humans(dynamic_cast<HUMMessage*>(message)->get_human_coordinates_());  // Hum Message is not very useful..
                break;
            case GameMessage::MessageType::NME:
                break; // Should not happen
            case GameMessage::MessageType::SET:
                game = new Game(dynamic_cast<SETMessage*>(message)->get_rows(),
                                dynamic_cast<SETMessage*>(message)->get_rows(),
                                GameTeam::HUMAN); // Set team to HUMAN for start, it will be updated in further messages.
                break;
            case GameMessage::MessageType::UPD:
                game->update_state(dynamic_cast<UPDMessage*>(message)->get_updates());
                std::cout << game;
                break;
            case GameMessage::MessageType::MAP:
                // Will not happen
                break;
        }
        delete message;
    }
    std::cout << game;
    return 0;
}