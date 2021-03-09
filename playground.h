//
// Created by flgn on 17.02.21.
//

#ifndef PISKWORKY_PLAYGROUND_H
#define PISKWORKY_PLAYGROUND_H

#include "map"
#include "user_interface.h"
#include "player.h"
#include "memory"
#include "point.h"

using namespace std;

using cell = char;
using field = map<int, map<int, cell>>; //first x then y

class player;

class user_interface;

class playground {
public:
    field field1;

    unique_ptr<player> players[2];

    int min_x = 0, min_y = 0, max_x = 0, max_y = 0; //coordinates of extremal cells

    playground() {}

    playground(const playground &playg);

    playground &operator=(const playground &playg);

    void clear_field();

    void add_to_field(char sign, const point &coordinate);

    char get_sign(const point &p) const;

    void check_extremes(const point &last_p); //check min,max x,y

    bool is_solved(const point &last_move); //check if last_move contains to five in line

private:
    bool five_in_direction(const point &direction, const point &last_move) const;
};


#endif //PISKWORKY_PLAYGROUND_H
