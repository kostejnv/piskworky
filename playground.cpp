//
// Created by flgn on 17.02.21.
//

#include "playground.h"


void playground::check_extremal_for_last_point(const point &last_p) {
    if (max_x < last_p.x)
        max_x = last_p.x;
    if (min_x > last_p.x)
        min_x = last_p.x;
    if (max_y < last_p.y)
        max_y = last_p.y;
    if (min_y > last_p.y)
        min_y = last_p.y;
}

char playground::get_sign(const point &p) {
    return field1[p.x][p.y];
}

