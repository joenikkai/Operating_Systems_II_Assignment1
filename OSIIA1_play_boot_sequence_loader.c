#include "OSIIA1_terminal.h"
#include <ncurses/ncurses.h>

void OSIIA1_play_boot_sequence_loader(WINDOW **w, int curr_cyc,int total_cyc)
{
    int width = 0, height = 0, inner_width = 0, inner_height = 0;
    getmaxyx(*w, height, width);
    inner_height = height - 2;
    inner_width = width - 2;
    float progress = (float) curr_cyc/total_cyc;
    int p_width = (int)progress * inner_width - 1;
    mvwaddch(*w, 1,1, '[');
    mvwaddch(*w, 1, 1+inner_width, ']');
    for (int col = 0; col <= p_width;col ++)
    {
        if (col < p_width)
        {
            mvwaddch(*w,1,1+col, '=');
        }
        if (col==p_width)
        {
            mvwaddch(*w,1,1+col, '>');
        }
    }
    box(*w, 0, 0);
    wrefresh(*w);
}
