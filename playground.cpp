//
// Created by flgn on 17.02.21.
//

#include "playground.h"


bool playground::try_to_encrese_field(const point &last_p) {
    bool was_encrease = false;
    if (max_x < last_p.x) {
        max_x = last_p.x;
        was_encrease = true;
    }

    if (min_x > last_p.x) {
        min_x = last_p.x;
        was_encrease = true;
    }
    if (max_y < last_p.y) {
        max_y = last_p.y;
        was_encrease = true;
    }
    if (min_y > last_p.y) {
        min_y = last_p.y;
        was_encrease = true;
    }
    return was_encrease;
}

char playground::get_sign(const point &p) {
    if (field1.find(p.x) != field1.end()){
        if (field1[p.x].find(p.y) != field1[p.x].end()){
            return field1[p.x][p.y];
        }
    }
    return 0;
}

void playground::add_to_field(char sign, const point &coordinate, bool &was_encreased) {
    field1[coordinate.x][coordinate.y] = sign;
    was_encreased = try_to_encrese_field(coordinate);
}