//
// Created by flgn on 17.02.21.
//

#ifndef PISKWORKY_CONSOLE_COMUNICATOR_H
#define PISKWORKY_CONSOLE_COMUNICATOR_H

#include "ncurses.h"
#include <string>
#include "playground.h"
#include "point.h"
#include "memory"
#include "player.h"

using namespace std;

using coordinate_size = point;

class playground;
class player;

class console_comunicator {
public:
    static const int WINDOWS_LENGTH = 200;
    static const int WINDOWS_HIGH = 200;
    static const int GRID_FIRST_LINE = 5;
    static const int CELL_LENGTH = 4; // number of characters of one grid cell
    static const int GRID_LENGTH = 20;
    static const int GRID_HIGH = 20;

    point GRID_POS = point(0, 0); // windows position of first grid character
    point INIT_POINT = point(-10,-10); //real coordinates of left_up grid point
    point LAST_MOVE = point(0,0); // real coordinates of last player move (needed for cursor shifting)

private:
public:


    WINDOW *win;
    console_comunicator();

    ~console_comunicator();

    void print_header(size_t turn);

    void print_centrelized(const string &text, size_t line);

    void print_right(const string &text, size_t line);

    void print_starting_screen(playground &p);

    void print_title();

    void print_player_turn(size_t turn);

    string get_string_line(size_t number_of_cell);

    string get_cells_interior(size_t number_of_cell);

    void print_grid(const playground &p); //return GRID_POS

    int get_fist_pos_of_centrilized_text(const string &text);

    int get_answer_from_centrilized_text(const string &text, size_t line);

    point convert_to_real_coordinate(const point &grid_p);

    bool try_convert_to_grid_coordinate(const point &real_p, point & grid_p);

    void fill_grid(const playground &playground);

    void print_field(const playground &playground);

    void print_playing_screen(const playground &playground);

    point get_coordinate_from_user(const playground &playground);

    void add_move(point move, char sign);

    bool print_winning_footer(int winner_id);

private:

};


#endif //PISKWORKY_CONSOLE_COMUNICATOR_H
