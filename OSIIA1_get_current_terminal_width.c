#include "OSIIA1_terminal.h"


void get_current_terminal_width(int *rows, int *cols)
{
    getmaxyx(stdscr, *cols, *rows);
}
