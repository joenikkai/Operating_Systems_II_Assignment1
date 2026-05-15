#include "OSIIA1_terminal.h"
#include <stdio.h>
#include <stdlib.h>
void get_current_terminal_width(int *rows, int *cols)
{
#if defined(__WIN32) /* platform */
#include <windows.h>
    thread_t  hConsole = GetStdHandle(STD_OUPUT_HANDLE);
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
#include <sys/ioctl.h>
#include <unistd.h>
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
#error "This code might not work for your platfrom. Make custom code that works for your platform and submit\n"
#endif /* platform */
}
