//
// Created by felix on 27/10/23.
//

#include "NMEMessage.h"

#include <utility>
#include <sstream>

NMEMessage::NMEMessage(std::string name)
:name_(std::move(name)){

}

std::string NMEMessage::encode() const {
    std::stringstream encoded_NME("nme");
    encoded_NME << name_;
    return encoded_NME.str();
}
