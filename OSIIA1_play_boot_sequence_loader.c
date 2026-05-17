#include "OSIIA1_terminal.h"
#include <ncurses/ncurses.h>

static float cubic_bezier(float t, float p1y, float p2y)
{
    float t2 = t * t;
    float t3 = t2 * t;
    float mt = 1.0f - t;
    float mt2 = mt * mt;
    return 3.0f * mt2 * t * p1y + 3.0f * mt * t2 * p2y + t3;
}

void OSIIA1_play_boot_sequence_loader(WINDOW **w, int curr_cyc, int total_cyc)
{
    if (!w || !*w)
        return;

    int width = 0, height = 0;
    getmaxyx(*w, height, width);

    int inner_width = width - 2;
    if (inner_width < 4)
        return;

    float progress = (float)curr_cyc / (float)total_cyc;
    if (progress > 1.0f)
        progress = 1.0f;
    if (progress < 0.0f)
        progress = 0.0f;

    // Cubic bezier easing (Ease In Out)
    float eased_progress = cubic_bezier(progress, 0.05f, 0.95f);

    int bar_width = inner_width - 2;
    int fill_len = (int)(eased_progress * bar_width);

    mvwaddch(*w, 1, 1, '[');
    for (int col = 0; col < bar_width; col++)
    {
        if (col < fill_len - 1)
        {
            mvwaddch(*w, 1, 2 + col, '=');
        }
        else if (col == fill_len - 1 && fill_len > 0)
        {
            mvwaddch(*w, 1, 2 + col, '>');
        }
        else
        {
            mvwaddch(*w, 1, 2 + col, ' ');
        }
    }
    mvwaddch(*w, 1, 1 + bar_width + 1, ']');

    box(*w, 0, 0);
    wrefresh(*w);
}
