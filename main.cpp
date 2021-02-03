#include <iostream>
#include <ncurses.h>

using namespace std;

int main(int argc, char *argv[]) {
    initscr();
    WINDOW * win = newwin(1000, 1000, 0, 0);
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


    return 0;
}
