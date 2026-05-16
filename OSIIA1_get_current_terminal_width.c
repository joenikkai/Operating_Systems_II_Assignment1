#include "OSIIA1_terminal.h"
#include <stdio.h>
#include <stdlib.h>
void get_current_terminal_width(int *rows, int *cols)
{
#if defined(__WIN32) /* platform */

    thread_t  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole,&csbi))
    {
        *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    else 
    {
        *rows = *cols = 0;
    }
#elif defined(__unix__)

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
#else
#error PLATFORM_COMPATIBILITY_ERROR 
#endif /* platform */
}
