//
// Created by flgn on 17.02.21.
//

#ifndef PISKWORKY_CONSOLE_COMUNICATOR_H
#define PISKWORKY_CONSOLE_COMUNICATOR_H

#include "ncurses.h"
#include <string>
#include "playground.h"
#include "point.h"
using namespace std;

using coordinate_size = point;

class playground;
class console_comunicator {
public:
    static const int WINDOWS_X_SIZE = 100;
    static const int WINDOWS_Y_SIZE = 100;
    static const int FIRST_LINE_GRID = 5;
    static const int CORIDOR_EDGE_LENGTH = 3;
    static const int CELL_LENGTH = 4;
    static const char PLAYER1_SIGN = 'X';
    static const char PLAYER2_SIGN = 'O';
private:
    WINDOW * win;


public:
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
    void print_grid(const playground &p);
    int get_fist_pos_of_centrilized_text(const string & text);
    int get_answer_from_centrilized_text(const string & text, size_t line);
private:

};


#endif //PISKWORKY_CONSOLE_COMUNICATOR_H
