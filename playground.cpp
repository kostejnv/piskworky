//
// Created by flgn on 17.02.21.
//

#include "playground.h"

playground::playground(const playground &playg) {
    field1 = playg.field1;
    min_x = playg.min_x;
    min_y = playg.min_y;
    max_x = playg.max_x;
    max_y = playg.max_y;
}

playground &playground::operator=(const playground &playg) {
    field1 = playg.field1;
    min_x = playg.min_x;
    min_y = playg.min_y;
    max_x = playg.max_x;
    max_y = playg.max_y;
    return *this;
}

void playground::clear_field() {
    field1.clear();
    min_x = 0;
    min_y = 0;
    max_x = 0;
    max_y = 0;
}

field playground::get_field() const {
    return field1;
}

char playground::get_sign(const point &p) const {
    if (field1.find(p.x) != field1.end()) {
        if (field1.at(p.x).find(p.y) != field1.at(p.x).end()) {
            return field1.at(p.x).at(p.y);
        }
    }
    return 0;
}

void playground::add_to_field(char sign, const point &coordinate) {
    field1[coordinate.x][coordinate.y] = sign;
}

void playground::check_extremes(const point &last_p) {

    if (max_x < last_p.x)
        max_x = last_p.x;

    if (min_x > last_p.x)
        min_x = last_p.x;

    if (max_y < last_p.y)
        max_y = last_p.y;

    if (min_y > last_p.y)
        min_y = last_p.y;
}

bool playground::five_in_direction(const point &direction, const point &last_move) const {
    char last_move_sign = get_sign(last_move);
    int signs_in_row = 1;
    for (int i = 1; i <= 5; ++i) {
        point next_cell(last_move.x + i * direction.x, last_move.y + i * direction.y);

        if (get_sign(next_cell) == last_move_sign)
            signs_in_row++;
        else
            break;
    }
    for (int i = 1; i <= 5; ++i) { //opposite direction
        point next_cell(last_move.x - i * direction.x, last_move.y - i * direction.y);

        if (get_sign(next_cell) == last_move_sign)
            signs_in_row++;
        else
            break;
    }
    return signs_in_row >= 5;
}

bool playground::is_solved(const point &last_move) {
    if (five_in_direction(point(1, 0), last_move))
        return true;

    if (five_in_direction(point(0, 1), last_move))
        return true;

    if (five_in_direction(point(1, 1), last_move))
        return true;

    if (five_in_direction(point(-1, 1), last_move))
        return true;

    return false;
}

