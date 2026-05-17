#include "input.h"
#include <string.h>

char *OSIIA1_add_history(WINDOW **win, char *input)
{
    if (!input || strlen(input) == 0 || !HISTORY_COMMANDS)
        return NULL;

    int current_count = 0;
    while (current_count < HISTORY_MAX && HISTORY_COMMANDS[current_count] != NULL)
    {
        current_count++;
    }

    // Avoid adding duplicate consecutive commands
    if (current_count > 0 && strcmp(HISTORY_COMMANDS[current_count - 1], input) == 0)
    {
        return input;
    }

    if (current_count < HISTORY_MAX)
    {
        HISTORY_COMMANDS[current_count] = strdup(input);
    }
    else
    {
        // History is full, shift everything left
        free(HISTORY_COMMANDS[0]);
        for (int i = 0; i < HISTORY_MAX - 1; i++)
        {
            HISTORY_COMMANDS[i] = HISTORY_COMMANDS[i + 1];
        }
        HISTORY_COMMANDS[HISTORY_MAX - 1] = strdup(input);
    }

    return input;
}
