#include <iostream>
#include <ncurses.h>
#include <sstream>
#include "playground.h"
#include "point.h"
#include "console_comunicator.h"

using namespace std;

int main(int argc, char *argv[]) {
    console_comunicator c;
    playground p;

/*    c.print_field(p);
    p.add_to_field('x',point(0,0));
    p.try_to_encrese_field(point(0,0));
    c.print_field(p);
    while(true);*/
    c.print_starting_screen(p);
    c.print_playing_screen(p);
    int index = 0;
    while (true) {
        point played_move = p.players[index % 2]->play(p);
        p.add_to_field(p.players[index % 2]->sign, played_move);
        if (p.try_to_encrese_field(played_move)) {
            /*stringstream sss;
            sss << p.min_y << "  " << p.max_y << "  " << p.min_x << "  " << p.max_x << "  ";
            for (const auto&[x, line] : p.field1) {
                for (const auto&[y, sign] : line) {
                    sss << y << "  " << x << "  ";
                }
            }
            wmove(c.win, 0,0);
            waddstr(c.win,sss.str().c_str());*/
            c.print_field(p);
        }
        else
            c.add_move(played_move, p.players[index % 2]->sign, p);
        if (p.is_solved(played_move))
            bool next_game = c.print_winning_footer(index % 2 + 1);
        index++;

    }


    return 0;
}
