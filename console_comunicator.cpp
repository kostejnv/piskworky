//
// Created by flgn on 17.02.21.
//

#include "console_comunicator.h"
#include "ncurses.h"
#include "sstream"

console_comunicator::console_comunicator() {
    initscr();
    win = newwin(WINDOWS_X_SIZE, WINDOWS_Y_SIZE, 0, 0);
    noecho();
}

console_comunicator::~console_comunicator() {
}

void console_comunicator::print_centrelized(const string &text, size_t line) {
    wmove(win, line, 0);
    wclrtoeol(win);
    size_t start_pos = get_fist_pos_of_centrilized_text(text);
    wmove(win, line, start_pos);
    waddstr(win, text.data());
    wrefresh(win);
}

void console_comunicator::print_right(const string &text, size_t line) {
    wmove(win, line, 0);
    wclrtoeol(win);
    wmove(win, line, 0);
    waddstr(win, text.c_str());
    wrefresh(win);
}

void console_comunicator::print_title() {
    print_centrelized("PISKWORKY", 0);
    print_centrelized("___________", 1);
}

void console_comunicator::print_player_turn(size_t turn) {
    if (turn == 1)
        print_centrelized("                  player 1 (X): It is your turn!           player 2 (O)                  ", 3);
    else
        print_centrelized("                  player 1 (X):                            player 2 (O): It is your turn!", 3);
}

void console_comunicator::print_header(size_t turn) {
    print_title();
    print_player_turn(turn);
}

string console_comunicator::get_string_line(size_t number_of_cell) {
    return string(number_of_cell*CELL_LENGTH+1, '-');
}

string console_comunicator::get_cells_interior(size_t number_of_cell) {
    stringstream sss;
    for (int i = 0; i < number_of_cell; ++i) {
        sss << "|   ";
    }
    sss << "|";
    return sss.str();
}

coordinate_size console_comunicator::get_grid_size(const playground &p) {
    int x_size, y_size;
    x_size = 2* CORIDOR_EDGE_LENGTH + p.max_x - p.min_x +1;
    y_size = 2* CORIDOR_EDGE_LENGTH + p.max_y - p.min_y +1;
    return coordinate_size(x_size, y_size);
}

void console_comunicator::print_grid(const playground &p) {
    coordinate_size size = get_grid_size(p);
    string line = get_string_line(size.y);
    string interior = get_cells_interior(size.y);
    for (int i = 0; i < size.x; ++i) {
        print_centrelized(line, FIRST_LINE_GRID + 2*i);
        print_centrelized(interior, FIRST_LINE_GRID + 2*i + 1);
    }
    print_centrelized(line, FIRST_LINE_GRID + 2*size.x);
}

int console_comunicator::get_fist_pos_of_centrilized_text(const string &text) {
    return WINDOWS_Y_SIZE / 2 - text.size() / 2;
}

int console_comunicator::get_answer_from_centrilized_text(const string &text, size_t line) {
    size_t first_x_choice = get_fist_pos_of_centrilized_text(text) + text.find_first_of('*');
    size_t second_x_choice = get_fist_pos_of_centrilized_text(text) + text.find_last_of('*');
    int choice = 0;
    bool pressed_enter = false;
    wmove(win, line, first_x_choice);
    wrefresh(win);
    while (true){

        char c = wgetch(win);
        switch (c) {
            // normal character handling
            case 'a':
                choice = 0;
                wmove(win, line, first_x_choice);
                break;
            case 'd':
                choice = 1;
                wmove(win, line, second_x_choice);
                break;
            case 10:
                pressed_enter = true;
                break;
            default:
                break;
        }
        wrefresh(win);
        if(pressed_enter)
            break;
    }

    return choice;
}

void console_comunicator::print_starting_screen(playground &p) {
    print_title();
    print_right("Player number 1 is: ", 2);
    string text = "*HUMAN          *COMPUTER";
    print_centrelized(text, 3);
    int answer = get_answer_from_centrilized_text(text,3);
    //TODO:ziskat player
    print_right("Player number 2 is: ", 5);
    print_centrelized(text, 6);
    answer = get_answer_from_centrilized_text(text,6);
}