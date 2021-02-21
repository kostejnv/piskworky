//
// Created by flgn on 21.02.21.
//

#ifndef PISKWORKY_HUMAN_PLAYER_H
#define PISKWORKY_HUMAN_PLAYER_H

#include "player.h"
#include "console_comunicator.h"
#include "point.h"

class human_player :  player {
public:
    virtual point play(const playground &playg) override;
    virtual std::string get_type() override;
    virtual ~human_player() {}
};


#endif //PISKWORKY_HUMAN_PLAYER_H
