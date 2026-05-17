#include "OSIIA1_terminal.h"


void get_current_terminal_dimensions()
{
    getmaxyx(stdscr, WINDOW_HEIGHT, WINDOW_WIDTH);
}
