#if !defined(INPUT_H)
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "OSIIA1_terminal.h"

#define HISTORY_FILE "."PROGRAM_NAME"_history"
#define HISTORY_MAX  100

extern char **HISTORY_COMMANDS;

void OSIIA1_read_history(char* filename);
void OSIIA1_stifle_history(int max);
void OSIIA1_write_history(char *filename);

char *OSIIA1_readline(WINDOW **win, char *prompt);
char *OSIIA1_add_history(WINDOW **win, char *input);
char *get_user_input();

#endif // INPUT_H