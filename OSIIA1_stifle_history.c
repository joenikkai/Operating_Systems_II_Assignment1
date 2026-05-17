#include "input.h"
#include <string.h>

void OSIIA1_stifle_history(int max)
{
    if (!HISTORY_COMMANDS || max <= 0)
        return;

    int current_count = 0;
    while (current_count < HISTORY_MAX && HISTORY_COMMANDS[current_count] != NULL)
    {
        current_count++;
    }

    if (current_count > max)
    {
        int to_remove = current_count - max;
        // Free the oldest ones
        for (int i = 0; i < to_remove; i++)
        {
            free(HISTORY_COMMANDS[i]);
        }
        // Shift the rest
        for (int i = 0; i < max; i++)
        {
            HISTORY_COMMANDS[i] = HISTORY_COMMANDS[i + to_remove];
        }
        // Null out the rest
        for (int i = max; i < HISTORY_MAX; i++)
        {
            HISTORY_COMMANDS[i] = NULL;
        }
    }
}
