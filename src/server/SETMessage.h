//
// Created by felix on 20/10/23.
//

#ifndef DOMINATORIX_SETMESSAGE_H
#define DOMINATORIX_SETMESSAGE_H


#include "GameMessage.h"

class SETMessage : public GameMessage {
public:
    SETMessage(const char *data);

    const char* encode() const override;

    int get_rows() const;
    int get_columns() const;
private:
    int rows_;
    int columns_;
};


#endif //DOMINATORIX_SETMESSAGE_H
