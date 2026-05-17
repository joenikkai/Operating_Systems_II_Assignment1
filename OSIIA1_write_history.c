#include "input.h"

void OSIIA1_write_history(char *filename)
{
    if (!filename || !HISTORY_COMMANDS)
        return;

    FILE *file = fopen(filename, "w");
    if (!file)
        return;

    for (int i = 0; i < HISTORY_MAX && HISTORY_COMMANDS[i] != NULL; i++)
    {
        fprintf(file, "%s\n", HISTORY_COMMANDS[i]);
    }

    fclose(file);
}
