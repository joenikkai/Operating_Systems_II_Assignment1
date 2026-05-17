#include "OSIIA1_terminal.h"

void OSIIA1_play_boot_sequence_blink(WINDOW **w, int curr_cyc,const char* str)
{
    int width = 0, height = 0, inner_width = 0, inner_height = 0;
    getmaxyx(*w, height, width);
    inner_height = height - 2;
    inner_width = width - 2;
    box(*w,0,0);
    wrefresh(*w);
}
