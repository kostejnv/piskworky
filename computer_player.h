//
// Created by flgn on 01.03.21.
//

#ifndef PISKWORKY_COMPUTER_PLAYER_H
#define PISKWORKY_COMPUTER_PLAYER_H

#include "player.h"
#include "tuple"
#include "playground.h"
#include "vector"

using namespace std;

class playground;

class computer_player : public player {

private:
    const static int DEPTH = 2;

public:

    explicit computer_player(char sign) { this->sign = sign; }

    ~computer_player() override = default;

    point play(const playground &playg) override;

private:

    point get_best_move_algorithm(const playground &playg); //initial phase of alpha-beta pruning

    long int alpha_beta_pruning(const playground &playg, int depth, long int alpha, long int beta, bool this_player);

    long int static_evaluator(const playground &playg);

    static vector<point> get_possible_moves(const field &field1); //get every cell around marked cells

    tuple<int, int> signs_count_in_5_row(const playground &playg, const point &initial_point,
                                         const point &direction);
    //in 5 cells from initial point (left-up) in give direction
    //return count of this player sign (first) and rival player sign (second)

    char get_rival_sign();
};


#endif //PISKWORKY_COMPUTER_PLAYER_H
