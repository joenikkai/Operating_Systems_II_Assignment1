#include "input.h"
#include <string.h>

void OSIIA1_read_history(char *filename)
{
    if (!filename || !HISTORY_COMMANDS)
        return;

    FILE *file = fopen(filename, "r");
    if (!file)
        return;

    char line[1024];
    int count = 0;
    while (fgets(line, sizeof(line), file) && count < HISTORY_MAX)
    {
        line[strcspn(line, "\n")] = 0; // Remove newline
        if (strlen(line) > 0)
        {
            HISTORY_COMMANDS[count++] = strdup(line);
        }
    }
    fclose(file);
}
