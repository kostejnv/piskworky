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

class console_comunicator;
class playground {
    console_comunicator * c;
public:
    field field1;
    //unique_ptr<player> players[2];
    int min_x = 0, min_y = 0, max_x = 0, max_y = 0; //coordinates of extremal cells
    bool try_to_encrese_field(const point &last_p);
    void add_to_field(char sign, const point & coordinate, bool & was_encrease);
    char get_sign(const point &p);


private:
};


#endif //PISKWORKY_PLAYGROUND_H
