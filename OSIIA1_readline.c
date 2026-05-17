#include "input.h"
#include "OSIIA1_threads.h"
#include <string.h>

static void redraw_line(WINDOW *w, int start_y, int start_x, char *buffer, int pos)
{
    wmove(w, start_y, start_x);
    wclrtoeol(w);
    int len = strlen(buffer);
    for (int i = 0; i <= len; i++)
    {
        if (i == pos)
            wattron(w, A_REVERSE);
        
        if (i < len)
            waddch(w, buffer[i]);
        else if (i == len)
            waddch(w, ' '); // Cursor at end

        if (i == pos)
            wattroff(w, A_REVERSE);
    }
    wmove(w, start_y, start_x + pos);
    wrefresh(w);
}

char *OSIIA1_readline(WINDOW **win, char *prompt)
{
    if (!win || !*win)
        return NULL;

    WINDOW *w = *win;
    pthread_mutex_lock(&TERMINAL_MUTEX);
    keypad(w, TRUE);
    curs_set(0); // Use our own highlight cursor
    
    int start_y, start_x;
    wprintw(w, "%s", prompt);
    getyx(w, start_y, start_x);
    
    char *buffer = calloc(1024, sizeof(char));
    int pos = 0;
    int len = 0;
    
    redraw_line(w, start_y, start_x, buffer, pos);
    pthread_mutex_unlock(&TERMINAL_MUTEX);

    int ch;
    int history_idx = -1;
    int history_count = 0;
    if (HISTORY_COMMANDS)
    {
        while (history_count < HISTORY_MAX && HISTORY_COMMANDS[history_count] != NULL)
            history_count++;
    }

    while ((ch = wgetch(w)) != '\n' && ch != KEY_ENTER && ch != 13)
    {
        pthread_mutex_lock(&TERMINAL_MUTEX);
        if (ch == KEY_BACKSPACE || ch == 127 || ch == 8)
        {
            if (pos > 0)
            {
                memmove(&buffer[pos - 1], &buffer[pos], len - pos + 1);
                pos--;
                len--;
            }
        }
        else if (ch == KEY_DC)
        {
            if (pos < len)
            {
                memmove(&buffer[pos], &buffer[pos + 1], len - pos);
                len--;
            }
        }
        else if (ch == KEY_LEFT)
        {
            if (pos > 0) pos--;
        }
        else if (ch == KEY_RIGHT)
        {
            if (pos < len) pos++;
        }
        else if (ch == KEY_HOME)
        {
            pos = 0;
        }
        else if (ch == KEY_END)
        {
            pos = len;
        }
        else if (ch == KEY_UP)
        {
            if (history_count > 0)
            {
                if (history_idx == -1)
                    history_idx = history_count - 1;
                else if (history_idx > 0)
                    history_idx--;

                strcpy(buffer, HISTORY_COMMANDS[history_idx]);
                len = pos = strlen(buffer);
            }
        }
        else if (ch == KEY_DOWN)
        {
            if (history_idx != -1)
            {
                if (history_idx < history_count - 1)
                {
                    history_idx++;
                    strcpy(buffer, HISTORY_COMMANDS[history_idx]);
                    len = pos = strlen(buffer);
                }
                else
                {
                    history_idx = -1;
                    buffer[0] = '\0';
                    len = pos = 0;
                }
            }
        }
        else if (ch >= 32 && ch <= 126)
        {
            if (len < 1023)
            {
                memmove(&buffer[pos + 1], &buffer[pos], len - pos + 1);
                buffer[pos++] = ch;
                len++;
            }
        }
        redraw_line(w, start_y, start_x, buffer, pos);
        pthread_mutex_unlock(&TERMINAL_MUTEX);
    }
    
    pthread_mutex_lock(&TERMINAL_MUTEX);
    // Clear highlight before finishing
    wmove(w, start_y, start_x);
    wprintw(w, "%s\n", buffer);
    wrefresh(w);
    pthread_mutex_unlock(&TERMINAL_MUTEX);
    
    return buffer;
}
