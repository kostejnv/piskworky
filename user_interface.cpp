//
// Created by flgn on 17.02.21.
//

#include "user_interface.h"
#include "ncurses.h"
#include "sstream"
#include "iostream"
#include "human_player.h"
#include "computer_player.h"
#include "memory"

user_interface::user_interface() {
    initscr();
    win = newwin(WINDOWS_LENGTH, WINDOWS_HIGH, 0, 0);
    noecho();
}

user_interface::~user_interface() {
    echo();
    noraw();
    endwin();
}

void user_interface::print_starting_screen(playground &p) {

    print_title();
    print_right("Player number 1 is: ", 2);
    string text = "*HUMAN          *COMPUTER";
    print_centralized(text, 3);

    int answer = get_answer_from_centralized_text(text, 3);
    if (answer == 0)
        p.players[0] = make_unique<human_player>('X', this);
    else
        p.players[0] = make_unique<computer_player>('X');

    print_right("Player number 2 is: ", 5);
    print_centralized(text, 6);

    answer = get_answer_from_centralized_text(text, 6);
    if (answer == 0)
        p.players[1] = make_unique<human_player>('O', this);
    else
        p.players[1] = make_unique<computer_player>('O');
}

void user_interface::print_player_turn(size_t turn) {
    if (turn == 1)
        print_centralized("                  player 1 (X): It is your turn!           player 2 (O)                  ",
                          3);
    else
        print_centralized("                  player 1 (X):                            player 2 (O): It is your turn!",
                          3);
}

void user_interface::print_playing_screen(const playground &playground) {
    wclear(win);
    print_header(1);
    print_field(playground);
}

point user_interface::get_coordinate_from_user(const playground &playground) {

    point actual_pos(0, 0);
    try_convert_to_grid_coordinate(LAST_MOVE, actual_pos);
    wmove(win, actual_pos.y, actual_pos.x);
    wrefresh(win);

    while (true) {
        char c = static_cast<char>(wgetch(win));

        switch (c) {
            case 10: {
                point selected_cell = convert_to_real_coordinate(actual_pos);
                if (playground.get_sign(selected_cell) == 0)
                    return selected_cell;
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

void user_interface::add_move(const point &move, char sign) {
    point grid_point(0, 0);
    if (try_convert_to_grid_coordinate(move, grid_point)) {
        wmove(win, grid_point.y, grid_point.x);
        waddch(win, sign);
    }

    LAST_MOVE = move;
}

bool user_interface::print_winning_footer(int winner_id) {
    int first_line_footer = GRID_POS.y + 2 * GRID_HIGH + 2;

    stringstream sss;
    sss << "Winner is player number " << winner_id << ". CONGRATULATIONS!";
    print_centralized(sss.str(), first_line_footer);
    print_right("Do you want to play revenge?", first_line_footer + 1);
    print_centralized("*YES            *NO", first_line_footer + 2);

    return get_answer_from_centralized_text("*YES            *NO", first_line_footer + 2) == 0;
}
//_____________________________________________________________________________________________
//      PRIVATE FUNCTIONS
//_____________________________________________________________________________________________

void user_interface::print_centralized(const string &text, size_t line) {
    wmove(win, line, 0);
    wclrtoeol(win);
    size_t start_pos = get_first_pos_of_centralized_text(text);
    wmove(win, line, start_pos);
    waddstr(win, text.data());
    wrefresh(win);
}

size_t user_interface::get_first_pos_of_centralized_text(const string &text) {
    return WINDOWS_HIGH / 2 - text.size() / 2;
}

void user_interface::print_right(const string &text, size_t line) {
    wmove(win, line, 0);
    wclrtoeol(win);
    wmove(win, line, 0);
    waddstr(win, text.c_str());
    wrefresh(win);
}

void user_interface::print_title() {
    print_centralized("PISKWORKY", 0);
    print_centralized("___________", 1);
}

void user_interface::print_header(size_t turn) {
    print_title();
    print_player_turn(turn);
}

int user_interface::get_answer_from_centralized_text(const string &text, size_t line) {

    size_t first_choice_x_position = get_first_pos_of_centralized_text(text) + text.find_first_of('*');
    size_t second_choice_x_position = get_first_pos_of_centralized_text(text) + text.find_last_of('*');
    int choice = 0;
    bool pressed_enter = false;

    wmove(win, line, first_choice_x_position);
    wrefresh(win);

    while (true) {
        char c = static_cast<char>(wgetch(win));

        switch (c) {
            case 'a':
                wmove(win, line, first_choice_x_position);
                choice = 0;
                break;
            case 'd':
                wmove(win, line, second_choice_x_position);
                choice = 1;
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

string user_interface::get_cell_line(size_t number_of_cell) {
    return string(number_of_cell * CELL_LENGTH + 1, '-');
}

string user_interface::get_cells_interior(size_t number_of_cell) {
    stringstream sss;
    for (int i = 0; i < number_of_cell; ++i) {
        sss << "|   ";
    }
    sss << "|";
    return sss.str();
}

void user_interface::print_grid(const playground &p) {

    string line = get_cell_line(GRID_LENGTH);
    string interior = get_cells_interior(GRID_HIGH);

    for (int i = 0; i < GRID_HIGH; ++i) {
        print_centralized(line, GRID_POS.y + 2 * i);
        print_centralized(interior, GRID_POS.y + 2 * i + 1);
    }
    print_centralized(line, GRID_POS.y + 2 * GRID_HIGH);
}

point user_interface::convert_to_real_coordinate(const point &grid_p) const {
    int x_real = INIT_POINT.x + (grid_p.x - GRID_POS.x - 2) / CELL_LENGTH;
    int y_real = INIT_POINT.y + (grid_p.y - GRID_POS.y - 1) / 2;
    return point(x_real, y_real);
}

bool user_interface::try_convert_to_grid_coordinate(const point &real_p, point &grid_p) const {

    if (real_p.x < INIT_POINT.x ||
        real_p.x >= INIT_POINT.x + GRID_LENGTH ||
        real_p.y < INIT_POINT.y ||
        real_p.y >= INIT_POINT.y + GRID_HIGH) //check if point in not out of grid
        return false;

    int x_grid = GRID_POS.x + 2 + CELL_LENGTH * (real_p.x - INIT_POINT.x);
    int y_grid = GRID_POS.y + 1 + 2 * (real_p.y - INIT_POINT.y);
    grid_p = point(x_grid, y_grid);
    return true;
}

void user_interface::fill_grid(const playground &playground) {

    for (const auto&[x, line] : playground.get_field()) {
        for (const auto&[y, sign] : line) {
            point grid_point(0, 0);
            if (try_convert_to_grid_coordinate(point(x, y), grid_point)) {
                wmove(win, grid_point.y, grid_point.x);
                waddch(win, sign);
            }
        }
    }
    wrefresh(win);
}

void user_interface::print_field(const playground &playground) {
    print_grid(playground);
    fill_grid(playground);
}