#include "main.h"
#include "OSIIA1_terminal.h"

void OSIIA1_print_horirontal_line(int *len, char *c)
{
    int l = WINDOW_WIDTH;
    if (len)
        l = *len;
    /* --- */
    char ch = '-';
    if (c)
        ch = *c;
    /* --- */
    for (int i = 0; i < l; i++)
    {
        putchar(c);
    }
}