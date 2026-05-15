#include "main.h"
#include "OSIIA1_terminal.h"

void OSIIA1_print_horirontal_line(int *len, char *c,int n)
{
    if (!n)
        return;
    /* --- */
    
    int l = 0;
    if (WINDOW_WIDTH)
        l = WINDOW_WIDTH;
    /* --- */
    if (len)
        l = *len;
    /* --- */
    if (!l)
        return;
    char ch = '-';
    if (c)
        ch = *c;
    /* --- */
    for (int i = 0; i < l; i++)
    {
        putchar(ch);
    }
    putchar('\n');
    if (n>0)
        OSIIA1_print_horirontal_line(len, c, n - 1);
}