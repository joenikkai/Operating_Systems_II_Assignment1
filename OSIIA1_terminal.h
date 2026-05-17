#if !defined(OSIIA1_TERMINAL_H)
#define OSIIA1_TERMINAL_H

#include <ncurses/ncurses.h>


extern volatile int WINDOW_WIDTH; /* \brief The width of the current terminal */
extern volatile int WINDOW_HEIGHT; /* \brief The height of the current terminal */

extern WINDOW *CPU_EXEC_LOG_WIN;
extern WINDOW *HANDLE_USER_INPUT_WIN;
extern WINDOW *GRANTT_CHART_DISPLAY_WIN;

void OSIIA1_play_boot_sequence(); /* animation for the dummy vm */

void OSIIA1_play_boot_sequence_log(WINDOW *w, int curr_cyc, char *logs[]); /* display logs akin to grub2 boot */
void OSIIA1_play_boot_sequence_loader(WINDOW* w, int curr_cyc); /* show a loading bar through time */
void OSIIA1_play_boot_sequence_blink(WINDOW* w, int curr_cyc); /* blink at intervals during the booting animation */

void get_current_terminal_dimensions();

#endif // OSIIA1_TERMINAL_H