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

    int cycles = (curr_cyc<inner_height)?curr_cyc:inner_height;

    box(*w, 0, 0);
    return;
    for (int cycle = 0; cycle < cycles; cycle++)
    {
        wrefresh(*w);
        if (cycle >= n_logs)
            return;
        size_t len = strlen(logs[cycle]);
        if (len == 3 && logs[cycle][0]=='<' && logs[cycle][2]== '>')
        {
            char ch = logs[cycle][1];
            mvwhline(*w,1+cycle,1,ch,inner_width);
            continue;
        }
        if (len >= inner_width)
            len = inner_width - 1;
        mvwprintw(*w, 1 + cycle, 1, "%.*s",len,logs[cycle]);
    }
    // for (int c = 0; c < no_of_lines_in_message; c++)
    //     mvwprintw(boot_msg_display_win, boot_msg_display_win_current_line++, 1, "%s", boot_messages[c]);
    // mvwhline(boot_msg_display_win, boot_msg_display_win_current_line++, 1, '=', boot_msg_display_win_width - 2);
    // mvwprintw(boot_msg_display_win, boot_msg_display_win_current_line++, 1, "Yay! Welcome, Dear user.");
    // mvwhline(boot_msg_display_win, boot_msg_display_win_current_line++, 1, '=', boot_msg_display_win_width - 2);
}
