#if !defined(OSIIA1_TERMINAL_H)
#define OSIIA1_TERMINAL_H

#include <sys/ioctl.h>
#include <sys/ioctl.h>
#include <unistd.h>

void get_current_terminal_width(int *rows, int *cols);
void OSIIA1_print_horirontal_line(int *len, char *c,int n);

#endif // OSIIA1_TERMINAL_H