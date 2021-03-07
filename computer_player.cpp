//
// Created by flgn on 01.03.21.
//

#include <sstream>
#include "computer_player.h"
#include "playground.h"
#include "climits"


std::string computer_player::get_type() {
    return "COMPUTER";
}

point computer_player::play(const playground &playg) {
    return alpha_beta_prunning_init(playg);
}

tuple<int, int> computer_player::get_numbers_of_played_cells_in_five_series(const playground &playg,
                                                                            const point &intial_point,
                                                                            const point &direction) {
    int my_sign = 0, rival_sign = 0;

    for (int i = 0; i < 5; ++i) {
        int x = intial_point.x + i * direction.x;
        int y = intial_point.y + i * direction.y;
        point actual(x, y);
        char actual_sign = playg.get_sign(actual);
        if (actual_sign == this->sign)
            ++my_sign;
        else {
            if (actual_sign == get_rival_sign())
                ++rival_sign;
        }
    }

    return tuple<int, int>(my_sign, rival_sign);
}

long int computer_player::static_evaluator(const playground &playg) {
    int me_n_in_row_count[6] = {0, 0, 0, 0, 0, 0};
    int rival_n_in_row_count[6] = {0, 0, 0, 0, 0, 0};
    for (int y = playg.min_y - 3; y <= playg.max_y + 3; ++y) {
        for (int x = playg.min_x - 3; x <= playg.max_x + 3; ++x) {
            point init_point(x, y);

            auto[me, rival] = get_numbers_of_played_cells_in_five_series(playg, init_point, point(1, 0));
            if (rival == 0)
                ++me_n_in_row_count[me];
            if (me == 0)
                ++rival_n_in_row_count[rival];

            tie(me, rival) = get_numbers_of_played_cells_in_five_series(playg, init_point, point(0, 1));
            if (rival == 0)
                ++me_n_in_row_count[me];
            if (me == 0)
                ++rival_n_in_row_count[rival];

            tie(me, rival) = get_numbers_of_played_cells_in_five_series(playg, init_point, point(1, 1));
            if (rival == 0)
                ++me_n_in_row_count[me];
            if (me == 0)
                ++rival_n_in_row_count[rival];

            tie(me, rival) = get_numbers_of_played_cells_in_five_series(playg, init_point, point(-1, 1));
            if (rival == 0)
                ++me_n_in_row_count[me];
            if (me == 0)
                ++rival_n_in_row_count[rival];
        }

    }

    long int evaluation = 0;
    if (rival_n_in_row_count[5] != 0) {
        evaluation = LONG_MIN + 1;
        return evaluation;
    }

    if (me_n_in_row_count[5] != 0) {
        evaluation = LONG_MAX;
        return evaluation;
    }
    evaluation += me_n_in_row_count[2] + me_n_in_row_count[3] * 4 + me_n_in_row_count[4] * 16;
    evaluation -= rival_n_in_row_count[2] + rival_n_in_row_count[3] * 4 + rival_n_in_row_count[4] * 16;

    return evaluation;

}

vector<point> computer_player::get_posibble_moves(const field &field1) {
    map<int, map<int, bool>> mask;
    for (const auto&[x, line] : field1) {
        for (const auto&[y, sign] : line) {
            mask[x][y] = false;
            for (int round_x = -1; round_x <= 1; ++round_x) {
                for (int round_y = -1; round_y <= 1; ++round_y) {
                    if (round_x == 0 && round_y == 0)
                        continue;
                    if (mask.find(x + round_x) == mask.end() ||
                        mask[x + round_x].find(y + round_y) == mask[x + round_x].end()) {
                        mask[x + round_x][y + round_y] = true;
                    }
                }

            }

        }
    }

    vector<point> neightboors;

    for (const auto&[x, line] : mask) {
        for (const auto&[y, value] : line) {
            if (value)
                neightboors.push_back(point(x, y));
        }
    }

    return neightboors;
}

point computer_player::alpha_beta_prunning_init(const playground &playg) {

    int depth = DEPTH;
    long int alpha = LONG_MIN;
    long int beta = LONG_MAX;
    point best_move(0, 0);

    auto neigboors = get_posibble_moves(playg.get_field());

    if (neigboors.size() == 1)
        return best_move;


    int index = 0;
    long int value = LONG_MIN;
    for (auto &&move : neigboors) {

        playground playg_with_next_move(playg);
        playg_with_next_move.add_to_field(this->sign, move);
        long int ab_value = alpha_beta_prunning(playg_with_next_move, depth - 1, alpha, beta, false);

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

long int computer_player::alpha_beta_prunning(const playground &playg, int depth, long int alpha, long int beta,
                                              bool this_player) {
    if (depth == 0) {
        return static_evaluator(playg);
    }

    auto neigboors = get_posibble_moves(playg.get_field());

    long int value;
    if (this_player) {
        value = LONG_MIN;
        for (auto &&move : neigboors) {
            playground playg_with_next_move(playg);
            playg_with_next_move.add_to_field(this->sign, move);
            value = max(value, alpha_beta_prunning(playg_with_next_move, depth - 1, alpha, beta, false));
            alpha = max(alpha, value);
            if (alpha >= beta)
                break;
        }
        return value;

    } else {
        value = LONG_MAX;
        for (auto &&move : neigboors) {
            playground playg_with_next_move(playg);
            playg_with_next_move.add_to_field(get_rival_sign(), move);
            value = min(value, alpha_beta_prunning(playg_with_next_move, depth - 1, alpha, beta, true));
            alpha = min(beta, value);
            if (alpha >= beta)
                break;
        }
        return value;

    }
}

char computer_player::get_rival_sign() {
    return (this->sign != 'X') ? 'X' : 'O';
}