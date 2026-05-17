#if !defined(OSIIA1_TERMINAL_H)
#define OSIIA1_TERMINAL_H

#include <ncurses/ncurses.h>


extern volatile int WINDOW_WIDTH; /* \brief The width of the current terminal */
extern volatile int WINDOW_HEIGHT; /* \brief The height of the current terminal */

extern WINDOW *CPU_EXEC_LOG_WIN;
extern WINDOW *HANDLE_USER_INPUT_WIN;
extern WINDOW *GRANTT_CHART_DISPLAY_WIN;

void get_current_terminal_dimensions();
void OSIIA1_print_horirontal_line(int *len, char *c, int n);

#endif // OSIIA1_TERMINAL_H