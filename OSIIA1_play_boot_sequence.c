#include "main.h"
#include "OSIIA1_terminal.h"
#include "timer.h"
#include <string.h>

void OSIIA1_play_boot_sequence()
{
    curs_set(0);

    const char *bs[] = BOOTING_SEQUENCE;
    int cyc_t = 150;                        /* cycle time - faster for reasonable boot */
    int nbs = (sizeof(bs) / sizeof(bs[0])); /* number of cycles */

    WINDOW *b_logger_d_w = newwin(WINDOW_HEIGHT - 3, WINDOW_WIDTH, 0, 0); /* boot log display window */
    if (!b_logger_d_w)
    {
        perror("newwin");
        exit(EXIT_FAILURE);
    }

    char *b = "Booting... ";                                                                   /* bootinng */
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

    box(b_logger_d_w, 0, 0);
    box(b_loading_bar_d_w, 0, 0);
    box(b_blinker_d_w, 0, 0);
    refresh();

    nodelay(stdscr, TRUE); // Enable non-blocking input for skipping

    for (int cyc = 0; cyc < nbs + 5; cyc++)
    {
        if (wgetch(stdscr) != ERR) // Skip if any key is pressed
            break;

        OSIIA1_play_boot_sequence_log(&b_logger_d_w, cyc, bs, nbs);
        OSIIA1_play_boot_sequence_loader(&b_loading_bar_d_w, cyc, nbs);
        OSIIA1_play_boot_sequence_blink(&b_blinker_d_w, cyc, b);
        OSIIA1_millisecond_sleep(cyc_t);
    }

    nodelay(stdscr, FALSE); // Disable non-blocking input

    OSIIA1_millisecond_sleep(200); // Small pause instead of 2 seconds
    delwin(b_logger_d_w);
    delwin(b_loading_bar_d_w);
    delwin(b_blinker_d_w);
    curs_set(1);
    clear();
    return;
}
