//
// Created by flgn on 17.02.21.
//

#include "console_comunicator.h"
#include "ncurses.h"
#include "sstream"
#include "iostream"
#include "human_player.h"
#include "memory"

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
        print_centrelized("                  player 1 (X): It is your turn!           player 2 (O)                  ",
                          3);
    else
        print_centrelized("                  player 1 (X):                            player 2 (O): It is your turn!",
                          3);
}

void console_comunicator::print_header(size_t turn) {
    print_title();
    print_player_turn(turn);
}

string console_comunicator::get_string_line(size_t number_of_cell) {
    return string(number_of_cell * CELL_LENGTH + 1, '-');
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
    x_size = 2 * CORIDOR_EDGE_LENGTH + p.max_x - p.min_x + 1;
    y_size = 2 * CORIDOR_EDGE_LENGTH + p.max_y - p.min_y + 1;
    return coordinate_size(x_size, y_size);
}

void console_comunicator::print_grid(const playground &p) {
    coordinate_size size = get_grid_size(p);
    string line = get_string_line(size.x);
    string interior = get_cells_interior(size.x);
    for (int i = 0; i < size.y; ++i) {
        print_centrelized(line, FIRST_LINE_GRID + 2 * i);
        print_centrelized(interior, FIRST_LINE_GRID + 2 * i + 1);
    }
    print_centrelized(line, FIRST_LINE_GRID + 2 * size.y);
    GRID_POS = point(get_fist_pos_of_centrilized_text(line), FIRST_LINE_GRID);
    FIRST_LINE_FOOTER = GRID_POS.y + size.y + 1;
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
    while (true) {

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
        if (pressed_enter)
            break;
    }

    return choice;
}

void console_comunicator::print_starting_screen(playground &p) {
    print_title();
    print_right("Player number 1 is: ", 2);
    string text = "*HUMAN          *COMPUTER";
    print_centrelized(text, 3);
    int answer = get_answer_from_centrilized_text(text, 3);
    if (answer == 0)
        p.players[0] = make_unique<human_player>();
    else
     exit(-1);
    //TODO: add computer player

    print_right("Player number 2 is: ", 5);
    print_centrelized(text, 6);
    answer = get_answer_from_centrilized_text(text, 6);
    if (answer == 0)
        p.players[1] = make_unique<human_player>();
    else
        exit(-1);
    //TODO: add computer player
}

point console_comunicator::convert_to_grid_coordinate(const point &p, const playground &playground) {
    int x_grid = GRID_POS.x + 2 + CELL_LENGTH * (p.x - playground.min_x + CORIDOR_EDGE_LENGTH);
    int y_grid = GRID_POS.y + 1 + 2 * (p.y - playground.min_y + CORIDOR_EDGE_LENGTH);
    return point(x_grid, y_grid);

}

point console_comunicator::convert_to_real_coordinate(const point &p, const playground &playground) {
    int x_real = playground.min_x - CORIDOR_EDGE_LENGTH + (p.x - GRID_POS.x - 2) / CELL_LENGTH;
    int y_real = playground.min_y - CORIDOR_EDGE_LENGTH + (p.y - GRID_POS.y - 1) / 2;
    return point(x_real, y_real);
}

void console_comunicator::fill_grid(const playground &playground) {
    for (const auto&[x, line] : playground.field1) {
        for (const auto&[y, sign] : line) {
            point grid_point = convert_to_grid_coordinate(point(x, y), playground);
            wmove(win, grid_point.y, grid_point.x);
            waddch(win, sign);
        }
    }
    wrefresh(win);
}

void console_comunicator::print_field(const playground &playground) {
    print_grid(playground);
    fill_grid(playground);
}

void console_comunicator::print_playing_screen(const playground &playground) {
    print_header(1);
    print_field(playground);
}

point console_comunicator::get_coordinate_from_user(const playground &playground) {

    point actual_pos = convert_to_grid_coordinate(point(0, 0), playground);
    bool cell_was_selected = false;

    while (true) {

        char c = wgetch(win);

        switch (c) {
            // normal character handling
            case 10:
                cell_was_selected = true;
                break;
            case 'w':
                if (convert_to_real_coordinate(point(actual_pos.x, actual_pos.y - 2), playground).y >=
                    playground.min_y - CORIDOR_EDGE_LENGTH) {
                    actual_pos.y -= 2;
                    wmove(win, actual_pos.y, actual_pos.x);
                }
                break;
            case 's':
                if (convert_to_real_coordinate(point(actual_pos.x, actual_pos.y + 2), playground).y <=
                    playground.max_y + CORIDOR_EDGE_LENGTH) {
                    actual_pos.y += 2;
                    wmove(win, actual_pos.y, actual_pos.x);
                }
                break;
            case 'd':
                if (convert_to_real_coordinate(point(actual_pos.x + CELL_LENGTH, actual_pos.y), playground).x <=
                    playground.max_x + CORIDOR_EDGE_LENGTH) {
                    actual_pos.x += CELL_LENGTH;
                    wmove(win, actual_pos.y, actual_pos.x);
                }
                break;
            case 'a':
                if (convert_to_real_coordinate(point(actual_pos.x - CELL_LENGTH, actual_pos.y), playground).x >=
                    playground.min_x - CORIDOR_EDGE_LENGTH) {
                    actual_pos.x -= CELL_LENGTH;
                    wmove(win, actual_pos.y, actual_pos.x);
                }
                break;
            default:
                break;

        }
        wrefresh(win);
        if (cell_was_selected)
            return actual_pos;
    }
}