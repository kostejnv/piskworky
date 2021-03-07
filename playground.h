//
// Created by flgn on 17.02.21.
//

#ifndef PISKWORKY_PLAYGROUND_H
#define PISKWORKY_PLAYGROUND_H

#include <map>
#include "console_comunicator.h"
#include "player.h"
#include <memory>
#include "point.h"

using namespace std;
using cell = char;
using field = map<int, map<int, cell>>; //first x then y

class player;

class console_comunicator;

class playground {
public:
    field field1;
    unique_ptr<player> players[2];
    static const int INITIAL_SIZE = 5;
    int min_x = -INITIAL_SIZE, min_y = -INITIAL_SIZE, max_x = INITIAL_SIZE, max_y = INITIAL_SIZE; //coordinates of extremal cells
    playground() {}
    playground(const playground & playg);
    playground& operator=(const playground & playg);
    bool try_to_encrese_field(const point &last_p);

    void add_to_field(char sign, const point &coordinate);

    char get_sign(const point &p) const;

    bool five_in_direction(point direction, const point &last_move);

    bool is_solved(const point &last_move);

    void clear_field();


private:
};


#endif //PISKWORKY_PLAYGROUND_H
