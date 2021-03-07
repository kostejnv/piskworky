//
// Created by flgn on 17.02.21.
//

#include "console_comunicator.h"
#include "ncurses.h"
#include "sstream"
#include "iostream"
#include "human_player.h"
#include "computer_player.h"
#include "memory"

console_comunicator::console_comunicator() {
    initscr();
    win = newwin(WINDOWS_LENGTH, WINDOWS_HIGH, 0, 0);
    noecho();
}

console_comunicator::~console_comunicator() {
    echo();
    noraw();
    endwin();
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

void console_comunicator::print_grid(const playground &p) {
    string line = get_string_line(GRID_LENGTH);
    string interior = get_cells_interior(GRID_HIGH);
    wmove(win, GRID_FIRST_LINE, 0);
    for (int i = 0; i < GRID_HIGH; ++i) {
        print_centrelized(line, GRID_FIRST_LINE + 2 * i);
        print_centrelized(interior, GRID_FIRST_LINE + 2 * i + 1);
    }
    print_centrelized(line, GRID_FIRST_LINE + 2 * GRID_HIGH);
    GRID_POS = point(get_fist_pos_of_centrilized_text(line), GRID_FIRST_LINE);
}


int console_comunicator::get_fist_pos_of_centrilized_text(const string &text) {
    return WINDOWS_HIGH / 2 - text.size() / 2;
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
        p.players[0] = make_unique<human_player>('X', this);
    else
        p.players[0] = make_unique<computer_player>('X', this);

    print_right("Player number 2 is: ", 5);
    print_centrelized(text, 6);
    answer = get_answer_from_centrilized_text(text, 6);
    if (answer == 0)
        p.players[1] = make_unique<human_player>('O', this);
    else
        p.players[1] = make_unique<computer_player>('O', this);
}

bool console_comunicator::try_convert_to_grid_coordinate(const point &real_p, point &grid_p) {
    if (real_p.x < INIT_POINT.x ||
        real_p.x >= INIT_POINT.x + GRID_LENGTH ||
        real_p.y < INIT_POINT.y ||
        real_p.y >= INIT_POINT.y + GRID_HIGH)
        return false;
    int x_grid = GRID_POS.x + 2 + CELL_LENGTH * (real_p.x - INIT_POINT.x);
    int y_grid = GRID_POS.y + 1 + 2 * (real_p.y - INIT_POINT.y);
    grid_p = point(x_grid, y_grid);
    return true;

}

point console_comunicator::convert_to_real_coordinate(const point &grid_p) {
    int x_real = INIT_POINT.x + (grid_p.x - GRID_POS.x - 2) / CELL_LENGTH;
    int y_real = INIT_POINT.y + (grid_p.y - GRID_POS.y - 1) / 2;
    return point(x_real, y_real);
}

void console_comunicator::fill_grid(const playground &playground) {
    for (const auto&[x, line] : playground.get_field()) {
        for (const auto&[y, sign] : line) {
            point grid_point = point(0, 0);
            if (try_convert_to_grid_coordinate(point(x, y), grid_point)) {
                wmove(win, grid_point.y, grid_point.x);
                waddch(win, sign);
            }
        }
    }
    wrefresh(win);
}

void console_comunicator::print_field(const playground &playground) {
    print_grid(playground);
    fill_grid(playground);
}

void console_comunicator::print_playing_screen(const playground &playground) {
    wclear(win);
    print_header(1);
    print_field(playground);
}

point console_comunicator::get_coordinate_from_user(const playground &playground) {

    point actual_pos = point(0,0);
    try_convert_to_grid_coordinate(LAST_MOVE, actual_pos);
    wmove(win,actual_pos.y, actual_pos.x);
    wrefresh(win);


    bool cell_was_selected = false;

    while (true) {

        char c = wgetch(win);

        switch (c) {
            // normal character handling
            case 10: {
                point selected_cell = convert_to_real_coordinate(actual_pos);
                if (playground.get_sign(selected_cell) == 0) {
                    return selected_cell;
                }
            }
                break;
            case 'w':
                if (convert_to_real_coordinate(point(actual_pos.x, actual_pos.y - 2)).y >=
                    INIT_POINT.y) {
                    actual_pos.y -= 2;
                } else {
                    INIT_POINT.y -= 1;
                    print_field(playground);
                }
                wmove(win, actual_pos.y, actual_pos.x);
                break;
            case 's':
                if (convert_to_real_coordinate(point(actual_pos.x, actual_pos.y + 2)).y <=
                    INIT_POINT.y + GRID_HIGH - 1) {
                    actual_pos.y += 2;
                } else {
                    INIT_POINT.y += 1;
                    print_field(playground);

                }
                wmove(win, actual_pos.y, actual_pos.x);
                break;
            case 'd':
                if (convert_to_real_coordinate(point(actual_pos.x + CELL_LENGTH, actual_pos.y)).x <=
                    INIT_POINT.x + GRID_LENGTH - 1) {
                    actual_pos.x += CELL_LENGTH;
                } else {
                    INIT_POINT.x += 1;
                    print_field(playground);
                }
                wmove(win, actual_pos.y, actual_pos.x);
                break;
            case 'a':
                if (convert_to_real_coordinate(point(actual_pos.x - CELL_LENGTH, actual_pos.y)).x >=
                    INIT_POINT.x) {
                    actual_pos.x -= CELL_LENGTH;
                } else {
                    INIT_POINT.x -= 1;
                    print_field(playground);
                }
                wmove(win, actual_pos.y, actual_pos.x);
                break;
            default:
                break;

        }
        wrefresh(win);
    }
}

void console_comunicator::add_move(point move, char sign) {
    LAST_MOVE = move;
    point grid_point = point(0, 0);
    if (try_convert_to_grid_coordinate(move, grid_point)) {
        wmove(win, grid_point.y, grid_point.x);
        waddch(win, sign);
    }
}

bool console_comunicator::print_winning_footer(int winner_id) { //true if player want next game
    int first_line_footer = GRID_POS.y + 2 * GRID_HIGH + 2;
    stringstream sss;
    sss << "Winner is player number " << winner_id << ". CONGRATULATIONS!";
    print_centrelized(sss.str(), first_line_footer);
    print_right("Do you want to play revenge?", first_line_footer + 1);
    print_centrelized("*YES            *NO", first_line_footer + 2);
    return get_answer_from_centrilized_text("*YES            *NO", first_line_footer + 2) == 0;
}