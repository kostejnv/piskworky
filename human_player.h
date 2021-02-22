//
// Created by flgn on 21.02.21.
//

#ifndef PISKWORKY_HUMAN_PLAYER_H
#define PISKWORKY_HUMAN_PLAYER_H

#include "player.h"
#include "console_comunicator.h"
#include "point.h"
#include "playground.h"


class human_player :   public player {
    console_comunicator * c;
public:
    human_player(char sign, console_comunicator *c) { this->sign = sign; this->c = c;}
    virtual point play(const playground &playg) override;
    virtual std::string get_type() override;
    virtual ~human_player() {}
};


#endif //PISKWORKY_HUMAN_PLAYER_H
