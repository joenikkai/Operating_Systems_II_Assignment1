#include "OSIIA1_terminal.h"
#include <ncurses/ncurses.h>

void OSIIA1_play_boot_sequence_loader(WINDOW **w, int curr_cyc, int total_cyc)
{
    int width = 0, height = 0;
    getmaxyx(*w, height, width);

    // int inner_height = height - 2;
    int inner_width = width - 2;
    float progress = (float)curr_cyc / total_cyc;
    int fill_len = (int)progress * inner_width - 2;
    if (fill_len > inner_width)
        fill_len = inner_width - 2;

    mvwaddch(*w, 1, 1, '[');
    for (int col = 0; col <= fill_len; col++)
    {
        if (col < fill_len)
        {
            mvwaddch(*w, 1, 1 + col, '=');
        }
        if (col == fill_len)
        {
            mvwaddch(*w, 1, 1 + col, '>');
        }
        else
        {
            mvwaddch(*w, 1, 1 + col, ' ');
        }
    }
    mvwaddch(*w, 1, 1 + fill_len, ']');
    box(*w, 0, 0);
    wrefresh(*w);
}
