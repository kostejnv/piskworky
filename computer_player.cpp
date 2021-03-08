//
// Created by flgn on 01.03.21.
//

#include <sstream>
#include "computer_player.h"
#include "playground.h"
#include "climits"


point computer_player::play(const playground &playg) {
    return get_best_move_algorithm(playg);
}

point computer_player::get_best_move_algorithm(const playground &playg) {

    int depth = DEPTH;
    long int alpha = LONG_MIN;
    long int beta = LONG_MAX;
    point best_move(0, 0);

    auto neighbors = get_possible_moves(playg.get_field());

    if (neighbors.size() == 1)
        return best_move;

    long int value = LONG_MIN;
    for (auto &&move : neighbors) {

        playground playg_with_next_move(playg);
        playg_with_next_move.add_to_field(this->sign, move);
        long int ab_value = alpha_beta_pruning(playg_with_next_move, depth - 1, alpha, beta, false);

        if (ab_value > value) {
            value = ab_value;
            best_move = move;
        }

        alpha = max(alpha, value);
        if (alpha >= beta)
            break;
    }
    return best_move;
}

long int computer_player::alpha_beta_pruning(const playground &playg, int depth, long int alpha, long int beta,
                                             bool this_player) {
    if (depth == 0) {
        return static_evaluator(playg);
    }

    auto neighbours = get_possible_moves(playg.get_field());

    long int value;
    if (this_player) {

        value = LONG_MIN;

        for (auto &&move : neighbours) {
            playground playg_with_next_move(playg);
            playg_with_next_move.add_to_field(this->sign, move);
            value = max(value, alpha_beta_pruning(playg_with_next_move, depth - 1, alpha, beta, false));

            alpha = max(alpha, value);

            if (alpha >= beta)
                break;
        }
        return value;

    } else {

        value = LONG_MAX;

        for (auto &&move : neighbours) {
            playground playg_with_next_move(playg);
            playg_with_next_move.add_to_field(get_rival_sign(), move);
            value = min(value, alpha_beta_pruning(playg_with_next_move, depth - 1, alpha, beta, true));

            alpha = min(beta, value);

            if (alpha >= beta)
                break;
        }
        return value;

    }
}

long int computer_player::static_evaluator(const playground &playg) {

    int n_signs_in_row_counts_of_this_player[6] = {0, 0, 0, 0, 0, 0};
    int n_signs_in_row_count_of_rival[6] = {0, 0, 0, 0, 0, 0};

    for (int y = playg.min_y - 3; y <= playg.max_y + 3; ++y) {
        for (int x = playg.min_x - 3; x <= playg.max_x + 3; ++x) {
            point init_point(x, y);

            auto[me, rival] = signs_count_in_5_row(playg, init_point, point(1, 0));
            if (rival == 0)
                ++n_signs_in_row_counts_of_this_player[me];
            if (me == 0)
                ++n_signs_in_row_count_of_rival[rival];

            tie(me, rival) = signs_count_in_5_row(playg, init_point, point(0, 1));
            if (rival == 0)
                ++n_signs_in_row_counts_of_this_player[me];
            if (me == 0)
                ++n_signs_in_row_count_of_rival[rival];

            tie(me, rival) = signs_count_in_5_row(playg, init_point, point(1, 1));
            if (rival == 0)
                ++n_signs_in_row_counts_of_this_player[me];
            if (me == 0)
                ++n_signs_in_row_count_of_rival[rival];

            tie(me, rival) = signs_count_in_5_row(playg, init_point, point(-1, 1));
            if (rival == 0)
                ++n_signs_in_row_counts_of_this_player[me];
            if (me == 0)
                ++n_signs_in_row_count_of_rival[rival];
        }

    }

    long int evaluation = 0;
    if (n_signs_in_row_count_of_rival[5] != 0) {
        evaluation = LONG_MIN + 1; // + 1 because of no winning strategy 
        return evaluation;
    }

    if (n_signs_in_row_counts_of_this_player[5] != 0) {
        evaluation = LONG_MAX;
        return evaluation;
    }
    evaluation += n_signs_in_row_counts_of_this_player[2] + n_signs_in_row_counts_of_this_player[3] * 4 +
                  n_signs_in_row_counts_of_this_player[4] * 16; //positive points for this player rows

    evaluation -= n_signs_in_row_count_of_rival[2] + n_signs_in_row_count_of_rival[3] * 4 +
                  n_signs_in_row_count_of_rival[4] * 16; //negative points for rival rows

    return evaluation;

}

vector<point> computer_player::get_possible_moves(const field &field1) {

    map<int, map<int, bool>> mask; // first x, second y

    for (const auto&[x, line] : field1) {
        for (const auto&[y, sign] : line) {

            mask[x][y] = false;
            for (int round_x = -1; round_x <= 1; ++round_x) {
                for (int round_y = -1; round_y <= 1; ++round_y) { //cells around marked cell

                    if (round_x == 0 && round_y == 0) //without marked cell
                        continue;

                    if (mask.find(x + round_x) == mask.end() ||
                        mask[x + round_x].find(y + round_y) == mask[x + round_x].end()) {
                        //if no value in mask on the point
                        mask[x + round_x][y + round_y] = true;
                    }
                }
            }
        }
    }

    vector<point> neighbours;

    for (const auto&[x, line] : mask) {
        for (const auto&[y, unsigned_cell] : line) {
            if (unsigned_cell)
                neighbours.emplace_back(point(x, y));
        }
    }

    return neighbours;
}


tuple<int, int> computer_player::signs_count_in_5_row(const playground &playg,
                                                      const point &initial_point,
                                                      const point &direction) {
    int my_sign_count = 0, rival_sign_count = 0;

    for (int i = 0; i < 5; ++i) {
        int x = initial_point.x + i * direction.x;
        int y = initial_point.y + i * direction.y;
        point actual_point(x, y);

        char actual_sign = playg.get_sign(actual_point);

        if (actual_sign == this->sign) {
            ++my_sign_count;
            continue;
        }
        if (actual_sign == get_rival_sign()) {
            ++rival_sign_count;
            continue;
        }
    }

    return tuple<int, int>(my_sign_count, rival_sign_count);
}

char computer_player::get_rival_sign() {
    return (this->sign == 'X') ? 'O' : 'X';
}