//
// Created by felix on 20/10/23.
//

#include "HMEMessage.h"

const char *HMEMessage::encode() const {
    return nullptr; // We should not send this message
}

HMEMessage::HMEMessage(const char *data)
:row_(data[0]), col_(data[1]){

}

int HMEMessage::get_starting_row() const {
    return row_;
}

int HMEMessage::get_starting_col() const {
    return col_;
}