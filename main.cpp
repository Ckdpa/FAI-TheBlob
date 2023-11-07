#include <iostream>
#include <unistd.h>
#include "Game.h"
#include "server/Connection.h"
#include "server/NMEMessage.h"
#include "server/HMEMessage.h"
#include "server/HUMMessage.h"
#include "server/SETMessage.h"
#include "server/UPDMessage.h"


int main(int argc, char* argv[]) {
    auto connection = Connection("localhost", 5555);
    if (connection.connect_socket() < 0) {
        return -1;
    }
    { // Initiate our connection and declare ourselves
        GameMessage *name_msg = new NMEMessage("Dominatorix");
        connection.socket_write(*name_msg);
        delete name_msg;
    }
    // Initiate game
    bool is_running = true;
    Game* game = nullptr;
    auto i = 0;
    while (is_running) {
        if (not connection.pending_message()) {
            sleep(1);
            continue;
        }
        GameMessage* message = connection.read_socket();
        switch (message->get_message_type()) {
            case GameMessage::MessageType::END:
                if (game != nullptr) {
                    delete game;
                }
                break;
            case GameMessage::MessageType::BYE:
                if (game != nullptr) {
                    delete game;
                }
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
                                Game::Team::HUMAN); // Set team to HUMAN for start, it will be updated in further messages.
                break;
            case GameMessage::MessageType::UPD:
                game->update_state(dynamic_cast<UPDMessage*>(message)->get_updates());
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