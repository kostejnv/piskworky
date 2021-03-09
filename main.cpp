#include <iostream>
#include <ncurses.h>
#include <sstream>
#include "playground.h"
#include "point.h"
#include "user_interface.h"

using namespace std;

int main(int argc, char *argv[]) {
    user_interface c;
    playground p;

    c.print_starting_screen(p);

    bool want_play = true;
    while (want_play) {

        c.print_playing_screen(p);
        int index = 0;
        while (true) {
            c.print_player_turn(index % 2 + 1);

            point played_move = p.players[index % 2]->play(p);

            p.add_to_field(p.players[index % 2]->sign, played_move);
            p.check_extremes(played_move);
            c.add_move(played_move, p.players[index % 2]->sign);

            if (p.is_solved(played_move))
                break;

            index++;
        }

        want_play = c.print_winning_footer(index % 2 + 1);
        if (want_play)
            p.clear_field();
    }

    return 0;
}
