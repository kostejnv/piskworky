//
// Created by flgn on 17.02.21.
//

#ifndef PISKWORKY_PLAYER_H
#define PISKWORKY_PLAYER_H

#include "point.h"
#include "playground.h"

class playground;

class player {
    virtual point play(const playground &playg) = 0;
    virtual ~player() {}
};


#endif //PISKWORKY_PLAYER_H
