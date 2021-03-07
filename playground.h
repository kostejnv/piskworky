//
// Created by flgn on 17.02.21.
//

#ifndef PISKWORKY_PLAYGROUND_H
#define PISKWORKY_PLAYGROUND_H

#include "map"
#include "console_comunicator.h"
#include "player.h"
#include "memory"
#include "point.h"

using namespace std;

using cell = char;
using field = map<int, map<int, cell>>; //first x then y

class player;
class console_comunicator;

class playground {

    field field1;
public:
    unique_ptr<player> players[2];

    int min_x = 0, min_y = 0, max_x = 0, max_y = 0; //coordinates of extremal cells

    playground() {}

    playground(const playground & playg);

    playground& operator=(const playground & playg);

    void check_extremes(const point &last_p); //check min,max x,y

    void add_to_field(char sign, const point &coordinate);

    field get_field() const;

    char get_sign(const point &p) const;

    bool is_solved(const point &last_move);

    void clear_field();

private:
    bool five_in_direction(point direction, const point &last_move);
};


#endif //PISKWORKY_PLAYGROUND_H
