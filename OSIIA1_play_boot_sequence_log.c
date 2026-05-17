#include "OSIIA1_terminal.h"
#include <string.h>

void OSIIA1_play_boot_sequence_log(WINDOW **w, int curr_cyc,const char* logs[],int n_logs)
{
    /**
     * We truncate
     *  */
    if (!*w)
        return;
    int width = 0, height = 0, inner_width = 0, inner_height = 0;
    getmaxyx(*w,height,width);
    inner_height = height - 2;
    inner_width = width - 2;

    werase(*w);
    box(*w, 0, 0);

    int cycles = (curr_cyc < inner_height) ? curr_cyc : inner_height;

    for (int cycle = 0; cycle < cycles; cycle++)
    {
        if (cycle >= n_logs)
            break;
        size_t len = strlen(logs[cycle]);
        if (len == 3 && logs[cycle][0] == '<' && logs[cycle][2] == '>')
        {
            char ch = logs[cycle][1];
            mvwhline(*w, 1 + cycle, 1, ch, inner_width);
            continue;
        }
        if (len >= inner_width)
            len = inner_width - 1;
        mvwprintw(*w, 1 + cycle, 1, "%.*s", (int)len, logs[cycle]);
    }
    wrefresh(*w);
}
