#include "OSIIA1_terminal.h"
#include <stdio.h>
#include <stdlib.h>
void get_current_terminal_width(int *rows, int *cols)
{
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ,&w) == 0)
    {
        *rows = w.ws_row;
        *cols = w.ws_col;
    }
    else
    {
        *rows = *cols = 0;
    }
}
