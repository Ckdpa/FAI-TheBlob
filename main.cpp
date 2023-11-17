#include <iostream>
// #include <unistd.h> Not available on Windows
#include <io.h>
#include "game/Game.h"
#include "server/Connection.h"
#include "server/messages/NMEMessage.h"
#include "server/messages/HMEMessage.h"
#include "server/messages/HUMMessage.h"
#include "server/messages/SETMessage.h"
#include "server/messages/UPDMessage.h"
#include "server/messages/MOVMessage.h"
#include "server/MessageHandler.h"
#include "server/messages/MAPMessage.h"


int main(int argc, char* argv[]) {
    std::string ip("127.0.0.1");
    std::string port("5555");
    if (argc > 1) {
        ip = argv[argc - 2];
        port = argv[argc - 1];
    }
    auto msg_handler = MessageHandler("127.0.0.1", "5555");
    if (msg_handler.connect() != 0) {
        return -1;
    }
    if (!msg_handler.init_game("Dominatorix")) {
        return -1;
    }
    // Initiate game
    bool is_running = true;
    Game* game = nullptr;
    char home_row = 0;
    char home_col = 0;
    while (is_running) {
        // Sleep(5000);
        if (!msg_handler.pending_message()) {
            Sleep(1000); // 100 ms
            continue;
        }
        GameMessage* message = msg_handler.get_next_message();
        switch (message->get_message_type()) {
            case GameMessage::MessageType::END:
                delete game;
                game = nullptr;
                // Prepare for next game
                Sleep(2);
                if (!msg_handler.init_game("Dominatorix")) {
                    return -1;
                }
                break;
            case GameMessage::MessageType::BYE:
                delete game;
                game = nullptr;
                is_running = false;
                break;
            case GameMessage::MessageType::HME:

                home_row = dynamic_cast<HMEMessage*>(message)->get_starting_row();
                home_col = dynamic_cast<HMEMessage*>(message)->get_starting_col();
                break;
            case GameMessage::MessageType::HUM:
                std::cout << "Received HUM message" << std::endl;
                game->set_humans(dynamic_cast<HUMMessage*>(message)->get_human_coordinates_());  // Hum Message is not very useful...
                std::cout << "Used HUM message" << std::endl;
                break;
            case GameMessage::MessageType::NME:
                break; // Should not happen
            case GameMessage::MessageType::SET:
                game = new Game(dynamic_cast<SETMessage*>(message)->get_rows(),
                                dynamic_cast<SETMessage*>(message)->get_columns(),
                                GameTeam::HUMAN); // Set team to HUMAN for start, it will be updated in further messages.
                break;
            case GameMessage::MessageType::MAP:
                game->update_state(dynamic_cast<MAPMessage*>(message)->get_updates());
                game->set_home(home_row, home_col);
                break;
            case GameMessage::MessageType::UPD:
                game->update_state(dynamic_cast<UPDMessage*>(message)->get_updates());
                {
                    
                    // Generate the next move # TODO
                    //auto next_move = game->get_next_move();
                    //auto msg = new MOVMessage(next_move);
                    // Play the move
                    // msg_handler.send_message(msg);
                    // delete msg;
                }
                break;
        }
        delete message;
        if (game) {
            std::cout << *game;
        }
    }
    return 0;
}