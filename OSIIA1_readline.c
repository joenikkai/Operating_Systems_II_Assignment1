#include "input.h"
#include <string.h>

char *OSIIA1_readline(WINDOW **win, char *prompt)
{
    if (!win || !*win)
        return NULL;

    WINDOW *w = *win;
    keypad(w, TRUE);
    
    int start_y, start_x;
    wprintw(w, "%s", prompt);
    getyx(w, start_y, start_x);
    wrefresh(w);

    char *buffer = calloc(1024, sizeof(char));
    int pos = 0;
    int ch;
    int history_idx = -1;

    int history_count = 0;
    if (HISTORY_COMMANDS)
    {
        while (history_count < HISTORY_MAX && HISTORY_COMMANDS[history_count] != NULL)
        {
            history_count++;
        }
    }

    while ((ch = wgetch(w)) != '\n' && ch != KEY_ENTER && ch != 13)
    {
        if (ch == KEY_BACKSPACE || ch == 127 || ch == 8)
        {
            if (pos > 0)
            {
                pos--;
                buffer[pos] = '\0';
                int y, x;
                getyx(w, y, x);
                mvwaddch(w, y, x - 1, ' ');
                wmove(w, y, x - 1);
            }
        }
        else if (ch == KEY_UP)
        {
            if (history_count > 0)
            {
                if (history_idx == -1)
                    history_idx = history_count - 1;
                else if (history_idx > 0)
                    history_idx--;

                // Move to start of input and clear to end of line
                wmove(w, start_y, start_x);
                wclrtoeol(w);
                
                strcpy(buffer, HISTORY_COMMANDS[history_idx]);
                pos = strlen(buffer);
                wprintw(w, "%s", buffer);
            }
        }
        else if (ch == KEY_DOWN)
        {
            if (history_idx != -1)
            {
                if (history_idx < history_count - 1)
                {
                    history_idx++;
                    wmove(w, start_y, start_x);
                    wclrtoeol(w);
                    strcpy(buffer, HISTORY_COMMANDS[history_idx]);
                    pos = strlen(buffer);
                    wprintw(w, "%s", buffer);
                }
                else
                {
                    history_idx = -1;
                    wmove(w, start_y, start_x);
                    wclrtoeol(w);
                    buffer[0] = '\0';
                    pos = 0;
                }
            }
        }
        else if (ch >= 32 && ch <= 126)
        {
            if (pos < 1023)
            {
                buffer[pos++] = ch;
                buffer[pos] = '\0';
                waddch(w, ch);
            }
        }
        wrefresh(w);
    }
    wprintw(w, "\n");
    wrefresh(w);
    return buffer;
}
