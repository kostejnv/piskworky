#include <iostream>
#include <ncurses.h>
#include "playground.h"
#include "point.h"
#include "console_comunicator.h"

using namespace std;

int main(int argc, char *argv[]) {
    console_comunicator c;
    //c.print_title();
    //c.print_right("Player number 1 is: ", 2);
    playground p;
    c.print_starting_screen(p);
    //string text = "*HUMAN          *COMPUTER";
    //c.print_centrelized(text, 3);
    c.print_header(1);
    c.print_grid(p);
    while(true);
    /*
    playground p;
    p.min_x = 0;
    p.max_x = 3;
    p.min_y= 0;
    p.max_y = 3;
    console_comunicator a;
    a.print_header(1);
    a.print_grid(p);
    while(true);
    /*
    playground p;
    cout<< p.min_x;
    p.check_extremal_for_last_point(point(-2,2));
    cout<< p.min_x;
    /*
    field f;
    //f[0];
    //f[0][1] = 'a';
    int i = f[0][1];
    cout << i;
    /*

    initscr();
    WINDOW * win;
    win = newwin(100, 100, 0, 0);
    noecho();

    int x = 0;
    int y = 0;
    while (true) {

        char c = getch();

        switch (c) {
            // normal character handling
            case 10:
                waddch(win, 'X');
                wmove(win, y, x);
                break;
            case 'q':
                char *sss;
                wmove(win, 0,0);
                waddstr(win, "   ahoj");
                wmove(win, 0,0);
                winstr(win,sss);
                wmove(win, 5,5);
                waddstr(win, sss);
                break;
            case 'x':
                clear();
                break;
            case 'w':
                y -= 2;
                wmove(win, y, x);
                break;
            case 's':
                y += 2;
                wmove(win, y, x);
                break;
            case 'd':
                x += 2;
                wmove(win, y, x);
                break;
            case 'a':
                x -= 2;
                wmove(win, y, x);
                break;
            default:
                break;

        }
        wrefresh(win);
    }
     /**/


    return 0;
}
