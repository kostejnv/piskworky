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
    console_comunicator * c;
public:


    computer_player(char sign, console_comunicator *c) { this->sign = sign; this->c = c;}

    virtual point play(const playground &playg) override;

    virtual std::string get_type() override;

    virtual ~computer_player() {}

private:
    char get_rival_sign();
    const static int DEPTH = 2;
    tuple<int, int> get_numbers_of_played_cells_in_five_series(const playground &playg, const point &intial_point,
                                                               const point &direction);
    //first - count of my sign, second - count of rival

    long int static_evaluator(const playground &playg);

    vector<point> get_posibble_moves(const field &field1);

    point alpha_beta_prunning_init(const playground &playg);
    long int alpha_beta_prunning(const playground &playg, int depth, long int alpha, long int beta, bool this_player);

};


#endif //PISKWORKY_COMPUTER_PLAYER_H
