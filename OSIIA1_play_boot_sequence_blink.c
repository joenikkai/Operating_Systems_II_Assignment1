#include "OSIIA1_terminal.h"
#include <ncurses.h>
#include <string.h>

void OSIIA1_play_boot_sequence_blink(WINDOW **w, int curr_cyc,const char* str)
{
    int width = 0, height = 0, inner_width = 0, inner_height = 0;
    getmaxyx(*w, height, width);
    inner_height = height - 2;
    inner_width = width - 2;
    int len = strlen(str);
    if (len >= inner_width)
        len = inner_width;
    if (curr_cyc % 2 == 0)
        mvwprintw(*w, 1, 1, "%.*s", len, str);
    else
    {
        for (int i = 0; i < len; i++)
            mvwaddch(*w, 1, 1 + i, ' ');
    }
    box(*w, 0, 0);
    wrefresh(*w);
}
