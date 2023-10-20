//
// Created by felix on 20/10/23.
//

#include "SETMessage.h"

const char *SETMessage::encode() const {
    return nullptr; // We should no send SET messages
}

SETMessage::SETMessage(const char* data)
:rows_(data[0]), columns_(data[1]){
}

int SETMessage::get_rows() const {
    return rows_;
}

int SETMessage::get_columns() const {
    return columns_;
}
