#include "main.h"
#include "OSIIA1_terminal.h"
#include "timer.h"

void OSIIA1_play_boot_sequence() 
{
    curs_set(0);

    const char *bs[] = BOOTING_SEQUENCE;
    int cyc_t = 333333; /* cycle time */
    int nbs = (sizeof(bs) / sizeof(bs[0]));
    int boot_time = nbs*cyc_t;

    WINDOW *b_logger_d_w = newwin(WINDOW_HEIGHT - 3,WINDOW_WIDTH,0,0); /* boot log display window */
    if (!b_logger_d_w)
    {
        perror("newwin");
        exit(EXIT_FAILURE);
    }

    char *b = "Booting... "; /* bootinng */
    WINDOW *b_loading_bar_d_w = newwin(3, WINDOW_WIDTH - strlen(b) - 2, WINDOW_HEIGHT - 3, 0); /* boot loading bar display window */
    if (!b_loading_bar_d_w)
    {
        perror("newwin");
        exit(EXIT_FAILURE);
    }

    WINDOW *b_blinker_d_w = newwin(3, strlen(b) + 2, WINDOW_HEIGHT - 3, WINDOW_WIDTH - (strlen(b) + 2)); /* boot blink display window */
    if (!b_blinker_d_w)
    {
        perror("newwin");
        exit(EXIT_FAILURE);
    }

    refresh();


    for (int cyc = 0; cyc < boot_time; cyc+=cyc_t)
    {

        OSIIA1_millisecond_sleep(cyc_t);
        OSIIA1_play_boot_sequence_log(&b_logger_d_w,cyc,bs,nbs);
        OSIIA1_play_boot_sequence_loader(&b_loading_bar_d_w,cyc);
        OSIIA1_play_boot_sequence_blink(&b_blinker_d_w,cyc,b);
    }

    delwin(b_logger_d_w);
    delwin(b_loading_bar_d_w);
    delwin(b_blinker_d_w);
    curs_set(1);
    return;
}

