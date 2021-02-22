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
    static const int WINDOWS_X_SIZE = 200;
    static const int WINDOWS_Y_SIZE = 200;
    static const int FIRST_LINE_GRID = 5;
    static const int CORIDOR_EDGE_LENGTH = 3;
    static const int CELL_LENGTH = 4;
    static const char PLAYER1_SIGN = 'X';
    static const char PLAYER2_SIGN = 'O';
    point GRID_POS = point(0, 0);
    int FIRST_LINE_FOOTER = 5;
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

    coordinate_size get_grid_size(const playground &p);

    void print_grid(const playground &p); //return GRID_POS

    int get_fist_pos_of_centrilized_text(const string &text);

    int get_answer_from_centrilized_text(const string &text, size_t line);

    point convert_to_real_coordinate(const point &p, const playground &playground);

    point convert_to_grid_coordinate(const point &p, const playground &playground);

    void fill_grid(const playground &playground);

    void print_field(const playground &playground);

    void print_playing_screen(const playground &playground);

    point get_coordinate_from_user(const playground &playground);

    void add_move(point move, char sign, const playground &p);

    bool print_winning_footer(int winner_id);

private:

};


#endif //PISKWORKY_CONSOLE_COMUNICATOR_H
