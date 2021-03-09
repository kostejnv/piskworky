//
// Created by flgn on 17.02.21.
//

#ifndef PISKWORKY_USER_INTERFACE_H
#define PISKWORKY_USER_INTERFACE_H

#include "ncurses.h"
#include "string"
#include "playground.h"
#include "point.h"
#include "memory"
#include "player.h"

using namespace std;

class playground;

class player;

class user_interface {

private:
    static const int WINDOWS_LENGTH = 200;
    static const int WINDOWS_HIGH = 200;
    static const int CELL_LENGTH = 4; // number of characters of one grid cell
    static const int GRID_LENGTH = 20; //grid cell length
    static const int GRID_HIGH = 20; // grid cell high
    point GRID_POS = point(59, 5); // windows position of first grid character

    point INIT_POINT = point(-GRID_LENGTH / 2, -GRID_HIGH / 2); //real coordinates of left_up grid point
    point LAST_MOVE = point(0, 0); // real coordinates of last player move (needed for cursor shifting)

    WINDOW *win;

public:
    user_interface();

    ~user_interface();

    void print_starting_screen(playground &p); //print starting screen and set player (human x computer) in playground

    void print_playing_screen(const playground &playground); //print header and field

    void print_player_turn(size_t turn); //show which player should play (turn according to player -> 1 or 2)

    point get_coordinate_from_user(const playground &playground);   // get real coordinate that user selected
    // can shift with fields

    void add_move(const point &move, char sign); //add move to grid

    bool print_winning_footer(int winner_id); //return if player want to play a revenge

private:

    point convert_to_real_coordinate(const point &grid_p) const;

    bool try_convert_to_grid_coordinate(const point &real_p,
                                        point &grid_p) const;   // set grid_p and return true if point is in grid
                                                                // return false if point is out of grid

    void print_centralized(const string &text, size_t line);

    static size_t get_first_pos_of_centralized_text(const string &text); //return x coordinate of first char of string

    void print_right(const string &text, size_t line);

    void print_header(size_t turn);

    void print_title();

    int get_answer_from_centralized_text(const string &text,
                                         size_t line);  // return 0 if first choice was selected otherwise 1
                                                        // note: choices must be marked with *

    void print_grid(const playground &p);

    static string get_cell_line(size_t number_of_cell); // return "----" long according to number_of_cell

    static string get_cells_interior(size_t number_of_cell); // return "|   |" long according to number_of_cell

    void fill_grid(const playground &playground); // print signs to cells in grid

    void print_field(const playground &playground); // print and fill grid

};


#endif //PISKWORKY_USER_INTERFACE_H
