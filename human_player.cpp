//
// Created by flgn on 21.02.21.
//

#include "human_player.h"

std::string human_player::get_type() {
    return "HUMAN";
}

point human_player::play(const playground &playg) {
    return c->get_coordinate_from_user(playg);
}
